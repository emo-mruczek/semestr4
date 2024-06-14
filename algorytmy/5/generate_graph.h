#ifndef GENERATE_GRAPH_H
#define GENERATE_GRAPH_H

typedef struct Edge {
    float weight;
} Edge;

typedef struct Vertice {
    int number;
    Edge edges[];
} Vertice;

typedef struct Graph {
    int size;
    Vertice *vertices[];
} Graph;

void clean_graph(Graph *G);

Graph *make_graph(int size);

void print_graph(Graph *G);

#endif
