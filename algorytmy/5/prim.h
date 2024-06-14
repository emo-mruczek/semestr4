#ifndef PRIM_H
#define PRIM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>

int min(int size, double key[], bool mst[]) {
    double min = DBL_MAX;
    int min_index = 0;

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
}

#endif
