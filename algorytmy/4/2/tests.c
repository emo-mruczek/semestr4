
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define COMMAND_LEN 100
#define DATA_SIZE 2048
#define K_MAX 20

void results(const char *generator_type, const char *sort_type, int n) {
    FILE *pf;
    char command[COMMAND_LEN];
    char data[DATA_SIZE];

    snprintf(command, sizeof(command), "%s %d | %s", generator_type, n, sort_type);
    pf = popen(command, "r");

    if (!pf) {
        #pragma omp critical
        {
            fprintf(stderr, "Nie otwarto rury: %s\n", command);
        }
        return;
    }

    while (fgets(data, DATA_SIZE, pf) != NULL) {
        #pragma omp critical
        {
            printf("%d ", n);
            {
                fprintf(stdout, "%s", data);
                fflush(stdout);
            }
            printf("\n");
        }
    }

    if (pclose(pf) != 0) {
        #pragma omp critical
        {
            fprintf(stderr, "Nie zamknieto rury: %s\n", command);
        }
    }
}

int main() {
    int num_threads = omp_get_max_threads();
    omp_set_num_threads(num_threads);

//    printf("%d watkow\n", num_threads);

    #pragma omp parallel for collapse(2) schedule(dynamic)

    for (int n = 10000; n <= 100000; n += 10000) {
        for (int k = 1; k < K_MAX; k++) {
            // results("./generate_random", "./bst", n);
            results("./generate_ascending", "./bst", n);
        }
    }

    return 0;
}
