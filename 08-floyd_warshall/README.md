# What is this?

(2) Floyd–Warshall’s Algorithm is used to find the shortest paths between all pairs of vertices in a graph, 
where each edge in the graph has a weight. 
For a graph with N vertices:
Step 1: Initialize the shortest paths between any 2 vertices with Infinity.
Step 2: Find all pair shortest paths that use 0 intermediate vertices, 
then find the shortest paths that use 1 intermediate vertex and so on.. until using all N vertices as intermediate nodes.
Step 3: Minimize the shortest paths between any 2 pairs in the previous operation.
Step 4: For any 2 vertices (i,j), one should actually minimize the distances between this pair using the first K nodes, 
so the shortest path will be: min(dist[i][k]+dist[k][j],dist[i][j]).
dist[i][k] represents the shortest path that only uses the first K vertices, 
dist[k][j] represents the shortest path between the pair k,j. 
As the shortest path will be a concatenation of the shortest path from i to k, then from k to j.

# How to use?

## How to build?

```
./build.sh
```

# How to use?

```
mpirun -np <number of processes> ./build/main
```

# Note

Careful with communication overhead. For example, using `MPI_Bcast` over simple O(N^2) computation. Just do the O(N^2) at each process.

## k_owner and k_relative_row

The code presented is not easy to maintain. So, we presented an alternative algorithm. However, the alternative algorithm may have scalability limitations when the number of processes increases to the thousands.

```
    int max_rows_per_process = (vertices + size - 1) / size; // equivalent to ceil(vertices / size), but ceil is for double
    for (int k = 0; k < vertices; k++)
    {
        // Broadcast the k-th row of the distance vector
        double *k_row = (double *)malloc(vertices * sizeof(double));
        int k_owner;
        if (remainder == 0) {
            k_owner = k / max_rows_per_process;
        } else
        {
            k_owner = (k < remainder * max_rows_per_process) ? 
                      k / max_rows_per_process : 
                      (k - remainder) / (max_rows_per_process - 1);
        }

        if (rank == k_owner)
        {
            int k_relative_row;
            if (remainder == 0)
            {
                k_relative_row = max_rows_per_process == 1 ?
                                 0 : 
                                 k % max_rows_per_process;
            }
            else
            {
                k_relative_row = (k < remainder * max_rows_per_process) ? 
                                 k % max_rows_per_process : 
                                 (k - remainder) % (max_rows_per_process - 1);
            }
            memcpy(k_row, &local_distance[k_relative_row * vertices], vertices * sizeof(double));
        }
        MPI_Bcast(k_row, vertices, MPI_DOUBLE, k_owner, comm);
```

Alternatively, to enhance readability and maintainability, the computation of k"_owner"  can be implemented using the algorithm outlined in APPENDIX E. However, this approach may exhibit scalability limitations when the number of processes increases to the thousands. It is important to note that the experimental results presented do not utilize the alternative algorithm.

```
    // Determine the owner process and the relative row for each vertex
    int (*rows_owner)[2] = (int (*)[2])malloc(vertices * sizeof(int[2]));
    for (int i = 0; i < vertices; i++) {
        int owner_process = 0;
        // displs[owner_process] / vertices is the first row of the owner process
        // sendcounts[owner_process] / vertices is the number of rows of the owner process
        while (i >= displs[owner_process] / vertices + sendcounts[owner_process] / vertices) {
            owner_process++;
        }
        rows_owner[i][0] = owner_process; // process rank
        rows_owner[i][1] = i - displs[owner_process] / vertices; // relative row within the process
    }
```

Usage
```
        // Broadcast the k-th row of the distance vector
        double *k_row = (double *)malloc(vertices * sizeof(double));
        int k_owner = rows_owner[k][0];
        if (rank == k_owner)
        {
            int k_relative_row = rows_owner[k][1];
            memcpy(k_row, &local_distance[k_relative_row * vertices], vertices * sizeof(double));
        }
        MPI_Bcast(k_row, vertices, MPI_DOUBLE, k_owner, comm);
```