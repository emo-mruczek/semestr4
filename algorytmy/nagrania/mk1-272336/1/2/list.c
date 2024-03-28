#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void insert (list* given_list_ptr, int n) {
    element* new_element = (element*)malloc(sizeof(element)); //tworzymy element do wstawienia
    new_element->value = n;
    if (given_list_ptr->head != NULL) {  
        new_element->ptr_next = (given_list_ptr->head)->ptr_next;
        (given_list_ptr->head)->ptr_next = new_element;
    }
    else {
        new_element->ptr_next = new_element; //jesli lista jest pusta, element wskazuje sam na siebie
    }
    given_list_ptr->head = new_element; //head wskazuje teraz na nowy element
   // printf("%d\n", (*(given_list_ptr->head)).value);
   // printf("%d\n", (*(new_element->ptr_next)).value);
    given_list_ptr->numberOfElements++;
}

list merge (list first_list, list second_list) {

    if (first_list.head == NULL) {
        return second_list;
    }
    if (second_list.head == NULL) {
        return first_list;
    }

    element* ptr_in = first_list.head; //element, na ktory wstazywal head 1. listy (1. element)
    element* ptr_out = ptr_in->ptr_next; //element, na ktory wstazywal 1. element 1. listy
    ptr_in->ptr_next = second_list.head; // 1. element 1 listy wskazuje na 1 element 2. listy

    //szukam ostatniego elementu listy 2
    element* ptr_last = second_list.head;
    while (ptr_last->ptr_next != second_list.head) {
        ptr_last = ptr_last->ptr_next;
    }

    ptr_last->ptr_next = ptr_out; //ostatni element listy 2 wstazuje na drugi element listy 1
    first_list.head = ptr_last; //head wskazuje teraz na ostatni element 2 listy

    first_list.numberOfElements += second_list.numberOfElements;
    return first_list;    
}

//printowanie elementow listy
void print_list(list given_list) {
    element* ptr = given_list.head;
    if (ptr != NULL) {
        do {
            printf("%d ---> %d\n", ptr->value, (ptr->ptr_next)->value);
            ptr = ptr->ptr_next;
        } while (ptr != given_list.head);
    }
}

int search_list(list* given_list, int target_num) {
    element* curr = given_list->head;
    if (curr == NULL) {
        return -1;
    }
    else {
        int comparisons = 0;

        do {
        comparisons++;
        if (curr->value == target_num) {
            return comparisons;  // Znaleziono element
        }
        curr = curr->ptr_next;
    } while (curr != given_list->head);
    

    return comparisons;
    }
}
