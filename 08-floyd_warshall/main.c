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
#include "GRAPH_shortest_paths_floyd_warshall.h"
#include <stdlib.h>
#include <stdio.h>
#include <float.h>

int main(int argc, char **argv)
{
    int vertices = 3;
    int edges = 4;
    int isDirected = 1;
    double **graph;
    srand(0);
    if (GRAPH_random_graph(&graph, vertices, edges, isDirected) != 0)
    {
        printf("Error creating the graph\n");
        return -1;
    }
    
    // Print the graph
    printf("Graph:\n");
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (graph[i][j] == DBL_MAX)
            {
                printf("INF\t");
            }
            else
            {
                printf("%.1f\t", graph[i][j]);
            }
        }
        printf("\n");
    }

    double **dist;
    if (GRAPH_shortest_paths_floyd_warshall((const double * const *) graph, vertices, &dist) != 0)
    {
        printf("Error computing the shortest paths\n");
        return -1;
    }

    // Print the shortest paths
    printf("\nShortest paths:\n");
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (dist[i][j] == DBL_MAX)
            {
                printf("INF\t");
            }
            else
            {
                printf("%.1f\t", dist[i][j]);
            }
        }
        printf("\n");
    }

    // Free the graph
    for (int i = 0; i < vertices; i++)
    {
        free(graph[i]);
    }
    free(graph);

    // Free the distance matrix
    for (int i = 0; i < vertices; i++)
    {
        free(dist[i]);
    }
    free(dist);

    return 0;
}
