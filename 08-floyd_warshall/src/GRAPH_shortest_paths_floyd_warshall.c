#include "GRAPH_shortest_paths_floyd_warshall.h"
#include <stdlib.h>
#include <float.h>

int GRAPH_shortest_paths_floyd_warshall(const double * const *graph,
                                        int vertices,
                                        double ***distance)
{
    *distance = (double **)malloc(vertices * sizeof(double *));

    // Initialize the dist matrix with the same values as the graph
    for (int i = 0; i < vertices; i++)
    {
        (*distance)[i] = (double *)malloc(vertices * sizeof(double));
        for (int j = 0; j < vertices; j++)
        {
            (*distance)[i][j] = graph[i][j];
        }
    }

    // k is the intermediate vertex
    // i is the source vertex
    // j is the destination vertex
    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                // performance optimization
                // Skip if i and j are the same vertex
                if (i == j)
                {
                    continue;
                }

                // performance optimization
                // Skip if there is no edge between i and k or between k and j
                if ((*distance)[i][k] == DBL_MAX || (*distance)[k][j] == DBL_MAX){
                    continue;
                }

                // Skip if the distance between i and j is already shorter than the distance between i and k + k and j
                if ((*distance)[i][j] < (*distance)[i][k] + (*distance)[k][j])
                {
                    continue;
                }

                (*distance)[i][j] = (*distance)[i][k] + (*distance)[k][j];
            }
        }
    }

    return 0;
}