#include "GRAPH_max_edges.h"
#include "GRAPH_random_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

// the shortcoming of this function is that it doesn't create multigraphs
// the experiment goal is to do parallel computing, so we don't focus on the graph creation
int GRAPH_random_graph(double ***graph, int vertices, int edges, int isDirected)
{
    // Check if the number of edges is valid
    if (edges > GRAPH_max_edges(vertices, isDirected))
    {
        printf("Too many edges for the number of vertices\n");
        return -1;
    }

    *graph = (double **)malloc(vertices * sizeof(double *));

    // Initialize the graph with infinity
    for (int i = 0; i < vertices; i++)
    {
        (*graph)[i] = (double *)malloc(vertices * sizeof(double));
        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
            {
                (*graph)[i][j] = 0;
            }
            else
            {
                (*graph)[i][j] = DBL_MAX; // to represent the abscene of an edge between two vertices
            }
        }
    }

    // Create random edges
    for (int i = 0; i < edges; i++)
    {
        int source = rand() % vertices; // % vertices to make sure the edge is within the graph
        int destination = rand() % vertices;
        double weight = (double)(rand() % 100) + 1; // to avoid 0 weight, and this generates a random integer between 1 and 100

        // Avoid self loops and no duplicate edges / to guarantee the amount of edges created is the same as the input parameter
        if (source == destination || (*graph)[source][destination] != DBL_MAX)
        {
            i--; // Repeat this iteration
            continue;
        }

        // For directed graphs, you only set the weight for the edge from the source to the destination
        (*graph)[source][destination] = weight;
        if (isDirected)
        {
            continue;
        }

        // For undirected graphs, you set the weight for both edges
        (*graph)[destination][source] = weight;
    }

    return 0;
}