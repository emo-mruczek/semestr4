#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define COMMAND_LEN 50
#define DATA_SIZE 2048
#define K_MAX 1

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

//    printf("#random data for k = %d\n", K_MAX);
  //  printf("#N-compH-swapH-compQ-swapQ-compI-swapI\n");

  /*  for (int n = 10; n <= 50; n = n + 10) {
        for (int k = 0; k < K_MAX; k++) {
            printf("%d ", n);
            results("./generate_random", "./hybrid_sort", n);
            results("./generate_random", "./quick_sort", n);
            results("./generate_random","./insertion_sort", n);
            printf("\n");
        }
    }*/

   for (int n = 1000; n <= 50000; n = n + 1000) {
        
        for (int k = 0; k < K_MAX; k++) {
            printf("%d ", n);
            results("./generate_random", "./hybrid_sort", n);
            results("./generate_random", "./quick_sort", n);
            printf("\n");
        }
    }


 /*   for (int n = 10; n <= 50; n = n + 10) {
        for (int k = 0; k < K_MAX; k++) {
            printf("%d ", n);
            results("./generate_ascending", "./hybrid_sort", n);
            results("./generate_ascending", "./quick_sort", n);
            results("./generate_ascending","./insertion_sort", n);
            results("./generate_descending", "./hybrid_sort", n);
            results("./generate_descending", "./quick_sort", n);
            results("./generate_descending","./insertion_sort", n);
            printf("\n");
        }
    }*/
   return 0;
}
