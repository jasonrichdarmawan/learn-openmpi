#include "MPI_GRAPH_shortest_paths_floyd_warshall.h"
#include <stdlib.h>
#include <float.h>
#include <string.h>

int MPI_GRAPH_shortest_paths_floyd_warshall(const double *graph, 
                                            const int vertices, 
                                            double **distance, 
                                            MPI_Comm comm)
{
    int rank, size;
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);
    int local_rows = vertices / size;
    int remainder = vertices % size;
    if (rank < remainder)
    {
        local_rows++;
    }

    int *sendcounts = (int *)malloc(size * sizeof(int));
    int *displs = (int *)malloc(size * sizeof(int));

    int offset = 0;
    for (int i = 0; i < size; i++)
    {
        sendcounts[i] = vertices / size * vertices;
        if (i < remainder)
        {
            sendcounts[i] += vertices;
        }
        displs[i] = offset;
        offset += sendcounts[i];
    }

    // graph are distributed among the process in block-row fashion
    double *local_graph = (double *)malloc(local_rows * vertices * sizeof(double));
    MPI_Scatterv(graph, sendcounts, displs, MPI_DOUBLE,
                 local_graph, local_rows * vertices, MPI_DOUBLE,
                 0, comm);

    // Initialize the dist matrix with the same values as the graph
    double *local_distance = (double *)malloc(local_rows * vertices * sizeof(double));
    memcpy(local_distance, local_graph, local_rows * vertices * sizeof(double));

    // k is the intermediate vertex
    // i is the source vertex
    // j is the destination vertex
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

        for (int i = 0; i < local_rows; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                // performance optimization
                // Skip if there is no edge between i and k or between k and j
                if (local_distance[i * vertices + k] == DBL_MAX || k_row[j] == DBL_MAX)
                {
                    continue;
                }

                // Skip if the distance between i and j is already shorter than the distance between i and k + k and j
                int b = local_distance[i * vertices + k] + k_row[j];
                if (local_distance[i * vertices + j] < b)
                {
                    continue;
                }

                local_distance[i * vertices + j] = b;
            }
        }

        // Clean up
        free(k_row);
    }

    // the result vector c should be distributed among the processes as blocks.
    *distance = (double *)malloc(vertices * vertices * sizeof(double));
    MPI_Allgatherv(local_distance, local_rows * vertices, MPI_DOUBLE,
                   *distance, sendcounts, displs, MPI_DOUBLE,
                   comm);

    // Clean up
    free(sendcounts);
    free(displs);
    free(local_graph);
    free(local_distance);

    return 0;
}