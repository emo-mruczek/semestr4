#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <inttypes.h>
#include "generate_graph.h"



void saveMST(uint64_t size, uint64_t parent[], double **G) {
    printf("\nMST:\n");
    printf("wierzcholek \twaga\n");

    bool **MST = (bool **)malloc(size *sizeof(bool *));
    for (uint64_t i = 0; i < size; i++) {
        MST[i] = (bool *)malloc(size * sizeof(bool));
        
        for (uint64_t j = 0; j < size; j++) {
            MST[i][j] = false;
        }
    }

    for (uint64_t i = 1; i < size; i++) {
        printf("%" PRIu64 " - %" PRIu64 "\t\t%.6f \n", parent[i], i, G[i][parent[i]]);
        MST[parent[i]][i] = true;
        MST[i][parent[i]] = true;
    }

    printf("\nMST:\n");

    for (uint64_t i = 0; i < size; i++) {
        for (uint64_t j = 0; j < size; j++) {
            printf("%d ", MST[i][j]);
        }

        printf("\n");
    }

for (uint64_t i = 0; i < size; i++) {
        free(MST[i]);
    }
    free(MST);
}

uint64_t min(uint64_t size, double key[], bool mst[]) {
    double min = DBL_MAX;
    uint64_t min_index = 0;

    for (uint64_t i = 0; i < size; i++)  {
        if (mst[i] == false && key[i] < min) {
            min = key[i];
            min_index = i;
        }
    }

    return min_index;
}

void primMST(uint64_t size, double **G) {
    // tutaj trzymam MST
    uint64_t *parent = (uint64_t *)malloc(size *sizeof(uint64_t));

    // do brania minimalnej wagi (zachlannie)
    double *key = (double *)malloc(size *sizeof(double));


    // te wziete do MST
    bool *mst = (bool *)malloc(size *sizeof(bool));


    for (uint64_t i = 0; i < size; i++) {
        key[i] = DBL_MAX; //jako infinity
        mst[i] = false;
    }

    // biore pierwszy wierzcholek
    key[0] = 0.0;
    parent[0] = (uint64_t)-1; //jako root

    for (uint64_t i = 0; i < size - 1; i++) {
        uint64_t u = min(size, key, mst);
        mst[u] = true;

        for (uint64_t j = 0; j < size; j++) {
            if (G[u][j] && mst[j] == false && G[u][j] < key[j] ) {
                parent[j] = u;
                key[j] = G[u][j];
            }
        }

    }

    saveMST(size, parent, G);

    free(parent);
    free(key);
    free(mst);
}

int main() {

    printf("Podaj wielkosc grafu: ");
    int size;
    scanf("%d", &size);

    double **graph = (double **)malloc(size *sizeof(double *));
 for (int i = 0; i < size; i++) {
        graph[i] = (double *)malloc(size * sizeof(double));
    }
    make_graph(size, graph);

    printf("\nGraf:\n");

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.6f ", graph[i][j]);
        }

        printf("\n");
    }

    primMST(size, graph);


 for (int i = 0; i < size; i++) {
                    free(graph[i]);
                }

                free(graph);

    return 0;
}
