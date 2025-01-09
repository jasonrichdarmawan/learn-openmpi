#ifndef GRAPH_RANDOM_GRAPH_H
#define GRAPH_RANDOM_GRAPH_H

// the shortcoming of this function is that it doesn't create multigraphs
// the experiment goal is to do parallel computing, so we don't focus on the graph creation
int GRAPH_random_graph(double ***graph, int vertices, int edges, int isDirected);

#endif // GRAPH_RANDOM_GRAPH_H