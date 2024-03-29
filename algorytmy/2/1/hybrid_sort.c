#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int comp = 0;
int swap = 0;

void insertion(int lo, int hi, int A[], bool should_print) {
    for (int i = lo + 1; i <= hi; i++) {
        int value = A[i];
        int j = i;
        

        while (j > lo && A[j - 1] > value) {
            comp++;
                swap++;
                A[j] = A[j - 1];
                j--;
 if (should_print) {
            for (int k = 0; k <= hi; k++) {
            printf(", %d", A[k]);
            }
            printf("\n");
        }

        }
        comp++;

        A[j] = value;

           }
 }

int partition(int A[], int lo, int hi) {

    int pivot = A[hi];


    int index = lo;

    for (int i = lo; i < hi; i++) {
        comp++;
        if (A[i] <= pivot) {
            swap++;
            int temp = A[i];
            A[i] = A[index];
            A[index] = temp;
            index++;
        }
    }

    swap++;
    int temp = A[hi];
    A[hi] = A[index];
    A[index] = temp;

    return index;
}

void hybrid(int A[], int lo, int hi, bool should_print) {
    while (lo < hi) {
        if (hi - lo < 10) {
            insertion(lo, hi, A, should_print);
            break;
        } else {
            int pivot = partition(A, lo, hi);
            if (pivot - lo < hi - pivot) {
                hybrid(A, lo, pivot - 1, should_print);
                lo = pivot + 1;
            } else {
                hybrid(A, pivot + 1, hi, should_print);
                hi = pivot - 1;
            }

        if (should_print) {
            for (int k = 0; k <= hi; k++) {
                printf(", %d", A[k]);
            }
            printf("\n");
        }
        }
    }
}

int main(int argc, char *argv[]) {
    printf("Podaj dlugosc tablicy: ");
    int length;
    scanf("%d", &length);
    int A[length];
    int Init[length];


    for (int i = 0; i < length; i++) {
        int num;
        scanf("%d", &num);
        A[i] = num;
    }

    bool should_print = false;
 

    if (length < 40) {
        should_print = true;
    }


    if (should_print ) {
        printf("Tablica wejsciowa: ");
    
   
    for (int k = 0; k < length; k++) {
        if (should_print ) {
            printf(", %d", A[k]);
            Init[k] = A[k];
        }
    }}

    if (should_print) {
        printf("\n");
        printf("Kluczowe momenty:\n");
    }

    //właściwy algorytm
    hybrid(A, 0, length - 1, should_print);

    if (should_print) {
        printf("Tablica poczatkowa:\n");
        for (int k = 0; k < length; k++) {
            printf("%d, ", Init[k]);
        }
        printf("\n");
        printf("Tablica posortowana:\n");
        for (int k = 0; k < length; k++) {
            printf("%d, ", A[k]);
        }
        printf("\n");
    }

    printf("Łączna liczba porównan między kluczami: %d\n", comp);
    printf("Łączna liczba przestawień kluczy: %d\n", swap);

    return 0;
}
