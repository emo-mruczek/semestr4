//https://www.geeksforgeeks.org/flexible-array-members-structure-c/
//https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
// https://stackoverflow.com/questions/6218399/how-to-generate-a-random-number-between-0-and-1

#include <stdlib.h>
#include <stdio.h>
#include <sys/random.h>
#include <time.h>

typedef struct Edge {
    float weight;
} Edge;

typedef struct Verticle {
    int number;
    Edge edges[];
} Verticle;

typedef struct Graph {
    int size;
    Verticle *verticles[];
} Graph;

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Podaj liczbe wierzcholkow.\n");
        return 1;
    }

    int size = 0;
    sscanf(argv[1], "%d", &size);
    printf("Podana liczba wierzcholkow: %d\n", size);

    size_t graph_size = sizeof(Graph) + size *sizeof(Verticle *);
    Graph *G = (Graph *)malloc(graph_size);

    if (G == NULL) {
        fprintf(stderr, "Cos sie zepsulo przy grafie\n");
        return 1;
    }

    G->size = size;

    unsigned int seed;
    getrandom( &seed, sizeof(seed), 0);
    srandom(seed);

    size_t verticle_size = sizeof(Verticle) + size *sizeof(Edge);

    for (int i = 0; i < size; i++) {
        Verticle *verticle = (Verticle *)malloc(verticle_size);
        G->verticles[i] = verticle;

        if ( G->verticles[i] == NULL) {
            fprintf(stderr, "Cos sie zepsulo przy wierzcholku\n");
            return 1;
        }

        G->verticles[i]->number = i;
    }

    // liczba krawedzi to n(n-1)/2
    //int number_of_verticles = size *(size - 1) / 2;

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {

            double rand_weight = (double)random() / (double)((unsigned)RAND_MAX + 1);
            G->verticles[i]->edges[j].weight = rand_weight;
            G->verticles[j]->edges[i].weight = rand_weight;
        }
    }

    //printu printu

    printf("            ");

    for (int i = 0; i < size; i++) {
        printf("%12s%d", "Wierzcholek", G->verticles[i]->number);
    }

    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%12s%d", "Wierzcholek", G->verticles[i]->number);

        for (int j = 0; j < size; j++) {
            printf("%12.6f", G->verticles[i]->edges[j].weight);
        }

        printf("\n");
    }

    // czyściu czyściu
    for (int i = 0; i < size; i++) {
        free(G->verticles[i]);
    }

    free(G);

    return 0;
}
