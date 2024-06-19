#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <inttypes.h>
#include "prim.h"
#include "generate_graph.h"

#define K_MAX 10

int main() {
    int num_threads = omp_get_max_threads();
    omp_set_num_threads(num_threads);


    #pragma omp parallel for collapse(2) schedule(dynamic)

    for (int n = 1000; n <= 10000; n += 1000) {
        for (int k = 1; k < K_MAX; k++) {

            double **graph = (double **)malloc(n *sizeof(double *));

            if (graph == NULL) {
                fprintf(stderr, "Cos sie zepsulo przy grafie\n");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < n; i++) {
                graph[i] = (double *)malloc(n *sizeof(double));

                if (graph[i] == NULL) {
                    fprintf(stderr, "znowu przy grafie sie zepsulo graph[%d]\n", i);
                    exit(EXIT_FAILURE);
                }
            }

            make_graph(n, graph);


            bool **MST = (bool **)malloc(n *sizeof(bool *));

            if (MST == NULL) {
                fprintf(stderr, "cos przy MST\n");
                exit(EXIT_FAILURE);
            }

            for (int i = 0; i < n; i++) {
                MST[i] = (bool *)malloc(n *sizeof(bool));

                if (MST[i] == NULL) {
                    fprintf(stderr, "cos przy mstMST[%d]\n", i);
                    exit(EXIT_FAILURE);
                }

                for (int j = 0; j < n; j++) {
                    MST[i][j] = false;
                }
            }

            primMST(n, graph, MST);

            for (int l = 1; l < K_MAX; l++) {

                uint64_t rounds = calculate_rounds(MST, n);

                #pragma omp critical
                {
                    printf("%d %" PRIu64 "\n", n, rounds);

                    fflush(stdout);
                }

            }

            {
                for (int i = 0; i < n; i++) {
                    free(graph[i]);
                }

                free(graph);

                for (int i = 0; i < n; i++) {
                    free(MST[i]);
                }

                free(MST);
            }
        }
    }

    return 0;
}
