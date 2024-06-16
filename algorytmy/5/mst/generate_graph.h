#ifndef GENERATE_GRAPH_H
#define GENERATE_GRAPH_H

#include <sys/random.h>
#include <time.h>
#include <stdlib.h>
#include <inttypes.h>

void make_graph(uint64_t size, double **G) {

    unsigned int seed;
    getrandom( &seed, sizeof(seed), 0);
    srandom(seed);

    for (uint64_t i = 0; i < size; i++) {
        for (uint64_t j = i + 1; j < size; j++) {
            double rand_weight = (double)random() / (double)((unsigned)RAND_MAX + 1);

            G[i][j] = rand_weight;
            G[j][i] = rand_weight;
        }

        G[i][i] = 0.0;
    }
}

#endif
