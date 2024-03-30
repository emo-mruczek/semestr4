#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define COMMAND_LEN 50
#define DATA_SIZE 2048

void results(char generator_type[30], char sort_type[20], int n) {
    FILE *pf;
    char command[COMMAND_LEN];
    char data[DATA_SIZE];

    sprintf(command, "%s %d | %s", generator_type, n, sort_type);
    pf = popen(command, "r");

    if(!pf) {
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

    for (int n = 10; n <= 50; n = n + 10) {
        printf("%d ", n);
        results("./generate_random", "./hybrid_sort", n);
        results("./generate_random", "./quick_sort", n);
        results("./generate_random","./insertion_sort", n);
        printf("\n");
    }

    return 0;
}
