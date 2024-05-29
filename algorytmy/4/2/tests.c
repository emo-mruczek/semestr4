#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <omp.h>

#define COMMAND_LEN 50
#define DATA_SIZE 2048
#define K_MAX 20

void results(char generator_type[30], char sort_type[20], int n) {
    FILE *pf;
    char command[COMMAND_LEN];
    char data[DATA_SIZE];

    sprintf(command, "%s %d | %s", generator_type, n, sort_type);
    pf = popen(command, "r");

    if (!pf) {
        fprintf(stderr, "Nie otwarto rury.\n");
        return;
    }

    while (fgets(data, DATA_SIZE, pf) != NULL) {
        fprintf(stdout, "%s", data);
        fflush(stdout);
    }

    if (pclose(pf) != 0) {
        fprintf(stderr, "Nie zamknieto streamu\n");
    }
}

int main() {

    /* int tab[100];
     #pragma omp parallel for

     for (int i = 0; i < 100; i++) {
         tab[i] = i;
     }

     for (int i = 0; i < 100; i++) {
         printf("%d ", tab[i]);
     }*/

    for (int n = 10000; n <= 100000; n = n + 10000) {

        for (int k = 0; k < K_MAX; k++) {
            printf("%d ", n);
            results("./generate_random", "./bst", n);
            printf("\n");
        }
    }

    return 0;
}
