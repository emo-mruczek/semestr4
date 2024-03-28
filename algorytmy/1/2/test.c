#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main() {


    int T[10000];
    for(int i = 0; i < 10000; i++) {
        int num = (rand() % (100000 + 1));
        T[i] = num;
    }

    list L = {0, NULL};

    for(int i = 0; i < 10000; i++) {
        insert(&L, T[i]);
    }

//wyszukiwanie liczby, które są na liscie
    int sum = 0;
    for(int i = 0; i < 1000; i++) {
      int index = (rand() % (10000 + 1));  
     // printf("Searching value: %d\n", T[index]);
        int comp = search_list(&L, T[index]);
        sum += comp;
       // printf("Number of com: %d\n", comp);
    }

    int average1 = sum/1000;
    printf("Average cost 1.: %d\n", average1);

    sum = 0;
    for(int i = 0; i < 1000; i++) {
      int index = (rand() % (100000 + 1));  
      // printf("Searching value: %d\n", index);
        int comp = search_list(&L, index);
        sum += comp;
       //printf("Number of com: %d\n", comp);
    }

    int average2 = sum/1000;
    printf("Average cost 2.: %d\n", average2);
   
    return 0;
}
