#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int comp = 0;
int swap = 0;
bool should_print = false;

bool is_less(int a, int b) {
    comp++;

    if (a < b) {
        return true;
    } else {
        return false;
    }
}

bool is_equal(int a, int b) {
    comp++;

    if (a == b) {
        return true;
    } else {
        return false;
    }
}

bool is_less_equal(int a, int b) {
    comp++;
    
    if (a <= b) {
        return true;
    } else {
        return false;
    }
}

void exchange(int* a, int* b) {
    swap++;
    int temp = *a;
    *a = *b;
    *b = temp;
}


int search(int A[], int l, int r, int x) {
    if(r >= l) {
        int mid = l + (r - l) / 2;

        // jesli element jest na srodku
        if(is_equal(A[mid], x)) {
            return mid;
        }

        // jesli element jest mniejszy od srodka
        if(is_less(x, A[mid])) {
            return search(A, l, mid - 1, x);
        }

        // jesli element jest wiekszy od srodka
        return search(A, mid + 1, r, x);
    }

    // elementu nie ma w tablilcy
    return -1;
}

int binsearch(int A[], int l, int r, int x) {
    int res = search(A, l, r, x);

    if (res == -1) {
        return 0;
    } else {
        return 1;
    }
}

int main() {
    printf("Podaj dlugosc tablicy: \n");
    int length;
    scanf("%d", &length);

    printf("Podaj szukany element: \n");
    int stat;
    scanf("%d", &stat);

    printf("Podawaj wartosci tablicy: \n");

    int A[length];
    int Init[length];

    for (int i = 0; i < length; i++) {
        int num;
        scanf("%d", &num);
        A[i] = num;
        Init[i] = num;
    }

    if (length < 50) {
        should_print = true;
    }

    //właściwy algorytm
    int value = binsearch(A, 0, length - 1 , stat); //czy jest git??

    if (should_print) {
        printf("Tablica poczatkowa:\n");
        for (int k = 0; k < length; k++) {
            if(Init[k]/10 < 1) {
                printf("0%d ", Init[k]);
            } else {
                printf("%d ", Init[k]);
            }
        }
        printf("\n");

        printf("Czy znaleziono element: ");
        if (value == 1) {
            printf("tak\n");
        } else {
            printf("nie\n");
        }
    }

    printf("Łączna liczba porównan między kluczami: %d\n", comp);
    printf("Łączna liczba przestawień kluczy: %d\n", swap);

    return 0;
}


