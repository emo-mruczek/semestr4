#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include "generate_graph.h"

typedef struct Edge {
    int u;
    int v;
    double weight;
} Edge;


void printMST(int size, Edge mst[]) {
    printf("\nMST:\n");
    printf("wierzcholek \twaga\n");

    for (int i = 0; i < size; i++) {
        printf("%d - %d \t\t%.6f \n", mst[i].u, mst[i].v, mst[i].weight);
    }
}

//https://en.cppreference.com/w/c/algorithm/qsort
int cmp(const void *a, const void *b) {
    double res = ((Edge *)a)->weight - ((Edge *)b)->weight;
    return (res > 0) -  (res < 0); //sprytne!
}

int find(int belongs[], int i) {
    if (belongs[i] != i) {
        belongs[i] = find(belongs, belongs[i]);
    }

    return belongs[i];
}

void unionSets(int belongs[], int rank[], int x, int y) {
    int rootX = find(belongs, x);
    int rootY = find(belongs, y);

    if (rank[rootX] < rank[rootY]) {
        belongs[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        belongs[rootY] = rootX;
    } else {
        belongs[rootY] = rootX;
        rank[rootX]++;
    }
}

void kruskalMST(int size, double G[size][size]) {

    int belongs[size];
    int rank[size];
    Edge edges[size *size];
    int ind = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (G[i][j] != 0) {
                edges[ind].u = i;
                edges[ind].v = j;
                edges[ind].weight = G[i][j];
                ind++;
            }
        }
    }

    qsort(edges, ind, sizeof(Edge), cmp);

    for (int i = 0; i < size; i++) {
        belongs[i] = i;
    }

    int ind_new = 0;
    Edge mst[size];

    for (int i = 0; i < ind; i++) {
        int a = find(belongs, edges[i].u);
        int b = find(belongs, edges[i].v);

        if (a != b) {
            mst[ind_new] = edges[i];
            ind_new++;

            unionSets(belongs, rank, a, b);
        }
    }

    printMST(ind_new, mst);
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

    kruskalMST(size, graph);

    return 0;
}
