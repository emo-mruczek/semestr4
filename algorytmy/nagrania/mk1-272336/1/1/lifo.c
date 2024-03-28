#include <stdio.h> 
#include <stdlib.h> 

#define SIZE 50
int S[SIZE];
int top = 0;

void push(int a) {
    //sprawdzam czy nie przekroczy liczby elementow na stosie
    if (top + 1 > SIZE) {
        printf("Za duzo wartosci\n");  
    } else {
    S[top] = a;
    printf("Wstawiono %d na miejsce %d\n", a, top);
    top = top + 1;
    }
}

int pop() {
    //czy są jakies elementy na stosie
    if (top <= 0) {
        printf("Brak elementów w LIFO\n");
        return 0;
    }
    top = top - 1;
    printf("Zabrano %d\n", S[top]);
    return S[top + 1];
}





