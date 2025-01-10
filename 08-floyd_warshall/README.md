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