#ifndef GENERATE_GRAPH_H
#define GENERATE_GRAPH_H

typedef struct Vertice Vertice;

typedef struct Edge {
    double weight;
    Vertice *vertice;
} Edge;

struct Vertice {
    int number;
    Edge edges[];
};

typedef struct Graph {
    int size;
    Vertice *vertices[];
} Graph;

void clean_graph(Graph *G);

Graph *make_graph(int size);

void print_graph(Graph *G);

#endif
