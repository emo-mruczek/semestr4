#ifndef PRIM_H
#define PRIM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <inttypes.h>
#include "generate_graph.h"


uint64_t max_value(uint64_t *rounds, uint64_t size) {
    uint64_t max_round = rounds[0];

    for (uint64_t i = 1; i < size; i++) {
        if (max_round < rounds[i]) {
            max_round = rounds[i];
        }
    }

    return max_round;
}

uint64_t make_round(uint64_t vertice, bool *VISITED, bool **MST, uint64_t size) {

    uint64_t rounds = 0;
    uint64_t *children_rounds = (uint64_t *)malloc(size *sizeof(uint64_t));
    VISITED[vertice] = true;

    uint64_t ind = 0;

    for (uint64_t i = 0; i < size; i++ ) {
        if (MST[vertice][i] == true) {
            if (VISITED[i] == false) {
                uint64_t child_rounds = make_round(i, VISITED, MST, size);
                children_rounds[ind] = child_rounds;
                ind++;
            }
        }
    }

    if (ind != 0) {
        rounds = max_value(children_rounds, ind);
    }

    free(children_rounds);



    return rounds + 1;
}

uint64_t calculate_rounds(bool **MST, uint64_t size) {
    // printf("\nLicze liczbe rund...\n");

    bool *VISITED = (bool *)malloc(size *sizeof(uint64_t));

    unsigned int seed;
    getrandom( &seed, sizeof(seed), 0);
    srandom(seed);

    uint64_t rand_vertice = rand() % (size);

    for (uint64_t i = 1; i < size; i++) {
        VISITED[i] = false;
    }

    uint64_t min_rounds = make_round(rand_vertice, VISITED, MST, size);

    free(VISITED);

    return min_rounds;
}

void saveMST(uint64_t size, uint64_t parent[], double **G, bool **MST) {
    // printf("\nMST:\n");
    //  printf("wierzcholek \twaga\n");


    for (uint64_t i = 1; i < size; i++) {
        //  printf("%" PRIu64 " - %" PRIu64 "\t\t%.6f \n", parent[i], i, G[i][parent[i]]);
        MST[parent[i]][i] = true;
        MST[i][parent[i]] = true;
    }

    /* printf("\nMST:\n");

     for (uint64_t i = 0; i < size; i++) {
         for (uint64_t j = 0; j < size; j++) {
             printf("%d ", MST[i][j]);
         }

         printf("\n");
     }*/


    // printf("\nPotrzebne rundy: %" PRIu64 "\n", rounds);

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

void primMST(uint64_t size, double **G, bool **MST) {
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
    parent[0] = (uint64_t) -1; //jako root

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

    saveMST(size, parent, G, MST);

    free(parent);
    free(key);
    free(mst);
}

#endif
