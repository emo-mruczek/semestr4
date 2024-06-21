//https://github.com/Abhinavvenkatadri/03-Data-Structures/blob/master/Lec%2011%20-%20Miscellaneous%20Problems%20BT/9_Pass_information_to_all_nodes.cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <inttypes.h>
#include "generate_graph.h"

int64_t max_value_of_two(int64_t a, int64_t b) {
    return (a > b ? a : b);
}

int64_t max_value(int64_t *rounds, int64_t size) {
    int64_t max_round = rounds[0];

    for (int64_t i = 1; i < size; i++) {
        if (max_round < rounds[i]) {
            max_round = rounds[i];
        }
    }

    return max_round;
}

int64_t make_round(int64_t vertice, bool *VISITED, bool **MST, int64_t size) {

    int64_t rounds = -1;
    int64_t *children_rounds = (int64_t *)malloc(size *sizeof(int64_t));
    VISITED[vertice] = true;

    int64_t ind = 0;

    for (int64_t i = 0; i < size; i++ ) {
        if (MST[vertice][i] == true) {
            if (VISITED[i] == false) {
                int64_t child_rounds = make_round(i, VISITED, MST, size);
                children_rounds[ind] = child_rounds;
                ind++;
            }
        }
    }

    if (ind != 0) {
        rounds = max_value(children_rounds, ind);
        rounds = max_value_of_two(rounds, ind);
    }

    free(children_rounds);



    return rounds + 1;
}

int64_t calculate_rounds(bool **MST, int64_t size) {
    printf("\nLicze liczbe rund...\n");

    bool *VISITED = (bool *)malloc(size *sizeof(int64_t));

    unsigned int seed;
    getrandom( &seed, sizeof(seed), 0);
    srandom(seed);

    int64_t rand_vertice = rand() % (size);

    printf("Wybrany wierzcholek: %" PRId64, rand_vertice);

    for (int64_t i = 1; i < size; i++) {
        VISITED[i] = false;
    }

    int64_t min_rounds = make_round(rand_vertice, VISITED, MST, size);

    free(VISITED);

    return min_rounds;
}

void saveMST(int64_t size, int64_t parent[], double **G) {
    printf("\nMST:\n");
    printf("wierzcholek \twaga\n");

    bool **MST = (bool **)malloc(size *sizeof(bool *));

    for (int64_t i = 0; i < size; i++) {
        MST[i] = (bool *)malloc(size *sizeof(bool));

        for (int64_t j = 0; j < size; j++) {
            MST[i][j] = false;
        }
    }

    for (int64_t i = 1; i < size; i++) {
        printf("%" PRIu64 " - %" PRIu64 "\t\t%.6f \n", parent[i], i, G[i][parent[i]]);
        MST[parent[i]][i] = true;
        MST[i][parent[i]] = true;
    }

    printf("\nMST:\n");

    for (int64_t i = 0; i < size; i++) {
        for (int64_t j = 0; j < size; j++) {
            printf("%d ", MST[i][j]);
        }

        printf("\n");
    }

    int64_t rounds = calculate_rounds(MST, size);

    printf("\nPotrzebne rundy: %" PRIu64 "\n", rounds);

    for (int64_t i = 0; i < size; i++) {
        free(MST[i]);
    }

    free(MST);
}

int64_t min(int64_t size, double key[], bool mst[]) {
    double min = DBL_MAX;
    int64_t min_index = 0;

    for (int64_t i = 0; i < size; i++)  {
        if (mst[i] == false && key[i] < min) {
            min = key[i];
            min_index = i;
        }
    }

    return min_index;
}

void primMST(int64_t size, double **G) {
    // tutaj trzymam MST
    int64_t *parent = (int64_t *)malloc(size *sizeof(int64_t));

    // do brania minimalnej wagi (zachlannie)
    double *key = (double *)malloc(size *sizeof(double));


    // te wziete do MST
    bool *mst = (bool *)malloc(size *sizeof(bool));


    for (int64_t i = 0; i < size; i++) {
        key[i] = DBL_MAX; //jako infinity
        mst[i] = false;
    }

    // biore pierwszy wierzcholek
    key[0] = 0.0;
    parent[0] = -1; //jako root

    for (int64_t i = 0; i < size - 1; i++) {
        int64_t u = min(size, key, mst);
        mst[u] = true;

        for (int64_t j = 0; j < size; j++) {
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
        graph[i] = (double *)malloc(size *sizeof(double));
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
