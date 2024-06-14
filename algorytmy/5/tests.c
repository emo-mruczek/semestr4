
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <inttypes.h>
#include "prim.h"
#include "kruskal.h"
#include "generate_graph.h"

#define COMMAND_LEN 100
#define DATA_SIZE 2048
#define K_MAX 2

typedef struct results {
    double time_prime;
    double time_kruskal;
} results;

int main() {
    int num_threads = omp_get_max_threads();
    omp_set_num_threads(num_threads);

    printf("%d watkow\n", num_threads);

    #pragma omp parallel for collapse(2) schedule(dynamic)

    for (int n = 100; n <= 10000; n += 100) {
        for (int k = 1; k < K_MAX; k++) {

            double graph[n][n];
            make_graph(n, graph);

            // https://stackoverflow.com/questions/10192903/time-in-milliseconds-in-c
            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            primMST(n, graph);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            uint64_t delta_us_prim = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            kruskalMST(n, graph);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            uint64_t delta_us_kruskal = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

            #pragma omp critical
            printf("%d %lu %lu\n", n, delta_us_prim, delta_us_kruskal);
        }
    }

    return 0;
}
