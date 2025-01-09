#include "GRAPH_max_edges.h"

int GRAPH_max_edges(int vertices, int isDirected)
{
    if (isDirected)
    {
        return vertices * (vertices - 1);
    }

    return vertices * (vertices - 1) / 2;
}