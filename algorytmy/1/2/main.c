#include <stdlib.h>
#include <stdio.h>
#include "list.h"

int main() {

    list first_list = {0, NULL};
    list second_list = {0, NULL};

    for(int i = 11; i < 21; i++) {
        insert(&first_list, i);
        insert(&second_list, 2*i);
    }

    printf("1. lista:\n");
    print_list(first_list);
    printf("2. lista:\n");
    print_list(second_list);
    list merged_lists = merge(first_list, second_list);
    printf("Złaczane listy:\n");
    print_list(merged_lists);

    return 0;
}
