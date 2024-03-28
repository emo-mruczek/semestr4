#include <stdio.h> 
#include <stdlib.h> 

#define SIZE 50
int head;
int tail;
int Q[SIZE];
int num_elem = 0;

void enqueue(int x) {
    if (num_elem > SIZE - 1)
        printf("Za duzo wartosci\n");
    else { 
    Q[tail] = x;
    num_elem++;
    printf("Wstawiono %d na miejsce %d\n", x, tail);
    if (tail == sizeof(Q) / sizeof(Q[0])) 
        tail = 0;
    else  
        tail++;
    } 
}

int dequeue() {
    if (num_elem == 0) {
        printf("Brak wartości w FIFO\n");
        return 0;
    } else {
    int x = Q[head];
    num_elem--;
    printf("Zabrano %d\n", x);
    if (head == SIZE)
        head = 0; 
    else
        head++;
    return x;
    }
}
