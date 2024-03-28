#ifndef _LIST_H_
#define _LIST_H_


struct my_element {
    int value;
   struct my_element* ptr_next;
}; //element_init = {0, 0};

typedef struct my_element element;

struct my_list {
    int numberOfElements;
    element* head;
};

typedef struct my_list list;

void insert (list* given_list, int n);

list merge (list first_list, list second_list);

//printowanie elementow listy
void print_list(list given_list);

int search_list(list* given_list, int target_num);

#endif