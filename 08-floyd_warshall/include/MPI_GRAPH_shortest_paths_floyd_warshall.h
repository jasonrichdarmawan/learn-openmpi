#ifndef MPI_GRAPH_SHORTEST_PATHS_FLOYD_WARSHALL_H
#define MPI_GRAPH_SHORTEST_PATHS_FLOYD_WARSHALL_H

#include <mpi.h>

// OpenMPI requires contiguous memory for sending and receiving data
// In other words, if you have 2D array, please flatten it before calling this function
int MPI_GRAPH_shortest_paths_floyd_warshall(const double *graph, 
                                            const int vertices, 
                                            double **distance, 
                                            MPI_Comm comm);

#endif // MPI_GRAPH_SHORTEST_PATHS_FLOYD_WARSHALL_H