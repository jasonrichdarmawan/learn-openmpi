// (2) Floyd–Warshall’s Algorithm is used to find the shortest paths between all pairs of vertices in a graph, 
// where each edge in the graph has a weight. 
// For a graph with N vertices:
// Step 1: Initialize the shortest paths between any 2 vertices with Infinity.
// Step 2: Find all pair shortest paths that use 0 intermediate vertices, 
// then find the shortest paths that use 1 intermediate vertex and so on.. until using all N vertices as intermediate nodes.
// Step 3: Minimize the shortest paths between any 2 pairs in the previous operation.
// Step 4: For any 2 vertices (i,j), one should actually minimize the distances between this pair using the first K nodes, 
// so the shortest path will be: min(dist[i][k]+dist[k][j],dist[i][j]).
// dist[i][k] represents the shortest path that only uses the first K vertices, 
// dist[k][j] represents the shortest path between the pair k,j. 
// As the shortest path will be a concatenation of the shortest path from i to k, then from k to j.

#include "GRAPH_random_graph.h"
#include "flatten_2D_double.h"
#include "MPI_GRAPH_shortest_paths_floyd_warshall.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int vertices;
    double **graph;
    double *flattened_graph;
    srand(0);
    if (rank == 0)
    {
        vertices = 100;
        int edges = vertices * (vertices - 1);
        int isDirected = 1;
        if (GRAPH_random_graph(&graph, vertices, edges, isDirected) != 0)
        {
            printf("Error creating the graph\n");
            return -1;
        }
        flatten_2D_double((const double * const *)graph,
                          &flattened_graph,
                          vertices);
    }
    
    // Print the graph
    // if (rank == 0)
    // {
    //     printf("%d \t| Graph:\n", rank);
    //     for (int i = 0; i < vertices; i++)
    //     {
    //         printf("%d \t| ", rank);
    //         for (int j = 0; j < vertices; j++)
    //         {
    //             if (flattened_graph[i * vertices + j] == DBL_MAX)
    //             {
    //                 printf("INF\t");
    //             }
    //             else
    //             {
    //                 printf("%.1f\t", flattened_graph[i * vertices + j]);
    //             }
    //         }
    //         printf("\n");
    //     }
    // }

    // use optimal number of processes
    MPI_Bcast((void *)&vertices, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Comm newcomm = MPI_COMM_NULL;
    int color = (rank < vertices) ? 0 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &newcomm);
    if (newcomm == MPI_COMM_NULL)
    {
        MPI_Finalize();
        return 0;
    }

    // Start timing
    MPI_Barrier(newcomm);
    double start_time = MPI_Wtime();

    double *distance;
    if (MPI_GRAPH_shortest_paths_floyd_warshall(flattened_graph, 
                                                vertices, 
                                                &distance,
                                                newcomm) != 0)
    {
        printf("Error computing the shortest paths\n");
        return -1;
    }

    // End timing
    MPI_Barrier(newcomm);
    double end_time = MPI_Wtime();
    if (rank == 0)
    {
        double elapsed_time = end_time - start_time;
        printf("Elapsed time: %.0f µs\n", elapsed_time * 1e6);
    }

    // Print the shortest paths
    // if (rank == 0)
    // {
    //     printf("\n%d \t| Shortest paths:\n", rank);
    //     for (int i = 0; i < vertices; i++)
    //     {
    //         printf("%d \t| ", rank);
    //         for (int j = 0; j < vertices; j++)
    //         {
    //             if (distance[i * vertices + j] == DBL_MAX)
    //             {
    //                 printf("INF\t");
    //             }
    //             else
    //             {
    //                 printf("%.1f\t", distance[i * vertices + j]);
    //             }
    //         }
    //         printf("\n");
    //     }
    // }

    // Free the graph
    if (rank == 0)
    {
        for (int i = 0; i < vertices; i++)
        {
            free(graph[i]);
        }
        free(graph);
        free(flattened_graph);
    }

    // Free the distance matrix
    free(distance);

    MPI_Comm_free(newcomm);

    MPI_Finalize();

    return 0;
}
