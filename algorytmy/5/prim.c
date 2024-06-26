#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "generate_graph.h"


void printMST(int size, int parent[], double G[size][size]) {
    printf("\nMST:\n");
    printf("wierzcholek \twaga\n");

    for (int i = 1; i < size; i++) {
        printf("%d - %d \t\t%.6f \n", parent[i], i, G[i][parent[i]]);
    }
}

int min(int size, double key[], bool mst[]) {
    double min = DBL_MAX;
    int min_index;

    for (int i = 0; i < size; i++)  {
        if (mst[i] == false && key[i] < min) {
            min = key[i];
            min_index = i;
        }
    }

    return min_index;
}

void primMST(int size, double G[size][size]) {
    // tutaj trzymam MST
    int parent[size];

    // do brania minimalnej wagi (zachlannie)
    double key[size];

    // te wziete do MST
    bool mst[size];

    for (int i = 0; i < size; i++) {
        key[i] = DBL_MAX; //jako infinity
        mst[i] = false;
    }

    // biore pierwszy wierzcholek
    key[0] = 0.0;
    parent[0] = -1; //jako root

    for (int i = 0; i < size - 1; i++) {
        int u = min(size, key, mst);
        mst[u] = true;

        for (int j = 0; j < size; j++) {
            if (G[u][j] && mst[j] == false && G[u][j] < key[j] ) {
                parent[j] = u;
                key[j] = G[u][j];
            }
        }

    }

    printMST(size, parent, G);

}

int main() {

    printf("Podaj wielkosc grafu: ");
    int size;
    scanf("%d", &size);

    double graph[size][size];
    make_graph(size, graph);

    printf("\nGraf:\n");

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%.6f ", graph[i][j]);
        }

        printf("\n");
    }

    primMST(size, graph);

    return 0;
}
