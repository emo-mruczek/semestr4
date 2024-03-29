#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int comp = 0;
int swap = 0;


void alghoritm(int length, int A[], bool should_print) {
    int i = 1;
    while (i < length) {
        int j = i;
        while (j > 0) {
            //porównanie między kluczami
            comp++;
            if(A[j - 1] > A[j]) {
            // swap
            swap++;
            int temp = A[j];
            A[j] = A[j - 1];
            A[j - 1] = temp;
            j--;
            }
        }

        if (should_print) {
            for (int k = 0; k < length; k++) {
                printf(", %d", A[k]);
            }
            printf("\n");
        }
        i++;
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
    

   
    for (int k = 0, l = 0; k < length; k++, l++) {
        if (should_print ) {
            printf(", %d", A[l]);
            Init[l] = A[k];
        }
    }}

    if (should_print) {
        printf("\n");
        printf("Kluczowe momenty:\n");
    }

    //właściwy algorytm
    alghoritm(length, A, should_print);

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
