//https://www.geeksforgeeks.org/flexible-array-members-structure-c/
//https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
// https://stackoverflow.com/questions/6218399/how-to-generate-a-random-number-between-0-and-1

#include <stdlib.h>
#include <stdio.h>
#include <sys/random.h>
#include <time.h>
#include "generate_graph.h"


void clean_graph(Graph *G) {
    // czyściu czyściu
    for (int i = 0; i < G->size; i++) {
        free(G->vertices[i]);
    }

    free(G);
}

void print_graph(Graph *G) {

    printf("            ");

    for (int i = 0; i < G->size; i++) {
        printf("%12s%d", "Wierzcholek", G->vertices[i]->number);
    }

    printf("\n");

    for (int i = 0; i < G->size; i++) {
        printf("%12s%d", "Wierzcholek", G->vertices[i]->number);

        for (int j = 0; j < G->size; j++) {
            printf("%12.6f", G->vertices[i]->edges[j].weight);
        }

        printf("\n");
    }
}

Graph *make_graph(int size) {
    /*if (argc < 2 || argc > 3) {
        fprintf(stderr, "Podaj liczbe wierzcholkow.\n");
        return 1;
    }

    int size = 0;
    sscanf(argv[1], "%d", &size);
    printf("Podana liczba wierzcholkow: %d\n", size);*/

    size_t graph_size = sizeof(Graph) + size *sizeof(Vertice *);
    Graph *G = (Graph *)malloc(graph_size);

    if (G == NULL) {
        fprintf(stderr, "Cos sie zepsulo przy grafie\n");
        //return 1;
        return NULL;
    }

    G->size = size;

    unsigned int seed;
    getrandom( &seed, sizeof(seed), 0);
    srandom(seed);


    for (int i = 0; i < size; i++) {
        size_t vertice_size = sizeof(Vertice) + size *sizeof(Edge);
        Vertice *vertice = (Vertice *)malloc(vertice_size);
        G->vertices[i] = vertice;

        if ( G->vertices[i] == NULL) {
            fprintf(stderr, "Cos sie zepsulo przy wierzcholku\n");
            clean_graph(G);
            return NULL;
            //return 1;
        }

        vertice->number = i;
        G->vertices[i] = vertice;
    }

    // liczba krawedzi to n(n-1)/2
    //int number_of_vertices = size *(size - 1) / 2;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {

            double rand_weight = (double)random() / (double)((unsigned)RAND_MAX + 1);
            G->vertices[i]->edges[j].weight = rand_weight;
            G->vertices[i]->edges[j].vertice = G->vertices[j];
            G->vertices[j]->edges[i].weight = rand_weight;
            G->vertices[j]->edges[i].vertice = G->vertices[i];
        }
    }

    return G;
}
