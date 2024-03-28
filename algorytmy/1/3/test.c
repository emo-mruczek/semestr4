#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

bool rand_way() {
    int randm = (rand() % (1 - 0 + 1));
    //printf("RANDOM: %d\n", randm);
        if(randm == 0) {
        return false;
    }
    else {
        return true;
    }
}

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

/*list L = {0, NULL};
    int T[] = {0, 1, 2, 3, 4};
    for(int i = 0; i < 5; i++) {
        insert(&L, T[i]);
    }*/
   // print_list(L);
   // printf("%d", L.numberOfElements);    
    //printf("%d\n", T[random_index]);
    //int index = 1;

//wyszukiwanie liczby, które są na liscie
    int sum = 0;
    for(int i = 0; i < 1000; i++) {
        bool way = rand_way();
      int index = (rand() % (10000 + 1));  
     // printf("Searching value: %d\n", T[index]);
        int comp = search_list(&L, T[index], way);
        sum += comp;
       // printf("Number of com: %d\n", comp);
    }

    int average1 = sum/1000;
    printf("Average cost 1.: %d\n", average1);

    sum = 0;
    for(int i = 0; i < 1000; i++) {
        bool way = rand_way();
      int index = (rand() % (100000 + 1));  
      // printf("Searching value: %d\n", index);
        int comp = search_list(&L, index, way);
        sum += comp;
       //printf("Number of com: %d\n", comp);
    }

    int average2 = sum/1000;
    printf("Average cost 2.: %d\n", average2);

//sprawdz czy to dziala!!!!!!!!!!



    return 0;
}

