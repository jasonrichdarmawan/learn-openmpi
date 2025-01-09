#ifndef GRAPH_SHORTEST_PATHS_FLOYD_WARSHALL_H
#define GRAPH_SHORTEST_PATHS_FLOYD_WARSHALL_H

int GRAPH_shortest_paths_floyd_warshall(const double * const *graph,
                                        int vertices,
                                        double ***distance);

#endif // GRAPH_SHORTEST_PATHS_FLOYD_WARSHALL_H