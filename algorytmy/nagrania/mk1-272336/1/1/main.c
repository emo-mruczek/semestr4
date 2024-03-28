#include <stdio.h> 
#include <stdlib.h> 
#include "lifo.h"
#include "fifo.h"

int main() {
    int dum;

    printf("Dla LIFO:\n");

    for (int i = 0; i < 50; i++) {
        push(i);
    }

    push(1234);

    for (int i = 0; i < 50; i++) {
        dum = pop();
    }

    dum = pop();

    printf("Dla FIFO:\n");

    for (int i = 0; i < 50; i++) {
        enqueue(i);
    }

    enqueue(1234);

    for (int i = 0; i < 50; i++) {
        dum = dequeue();
    }

    dum = dequeue();

    return 0;
}
