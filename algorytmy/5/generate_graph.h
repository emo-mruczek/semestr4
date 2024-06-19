#ifndef GENERATE_GRAPH_H
#define GENERATE_GRAPH_H

#include <sys/random.h>
#include <time.h>
#include <stdlib.h>

void make_graph(int size, double G[size][size]) {

    unsigned int seed;
    getrandom( &seed, sizeof(seed), 0);
    srandom(seed);

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {

            double rand_weight = (double)random() / (double)((unsigned)RAND_MAX + 1);

            G[i][j] = rand_weight;
            G[j][i] = rand_weight;
        }

        G[i][i] = 0;
    }
}

#endif
