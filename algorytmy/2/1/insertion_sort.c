#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int comp = 0;
int swap = 0;

bool is_less(int a, int b, bool count) {
    if (count) {
      comp++;
    }

    if (a < b) {
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

void alghoritm(int length, int A[], bool should_print) {
    int i = 1;
    while (i < length) {
       int j = i;
       while (j > 0 && is_less(A[j], A[j-1], true))  {
            exchange(&A[j], &A[j-1]);
            j--;     
       }

       if (should_print) {
            for (int k = 0; k < length; k++) {
                printf(" %d", A[k]);
            }
            printf("\n");
       }

       i++;
    }
}

 bool is_sorted(int A[], int length) {
    for (int i = 0; i < length - 1; i++) {
        if (A[i] > A[i + 1]) {
            return false;
        }
    }
    return true;
}

int main() {
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
            printf(" %d", A[k]);
            Init[k] = A[k];
    }

        printf("\n");
        printf("Kluczowe momenty:\n");
    }
    
    //właściwy algorytm
    alghoritm(length, A, should_print);

    if (should_print) {
        printf("Tablica poczatkowa:\n");
        for (int k = 0; k < length; k++) {
            printf("%d ", Init[k]);
        }
        printf("\n");
        printf("Tablica posortowana:\n");
        for (int k = 0; k < length; k++) {
            printf("%d ", A[k]);
        }
        printf("\n");
    }

    printf("Łączna liczba porównan między kluczami: %d\n", comp);
    printf("Łączna liczba przestawień kluczy: %d\n", swap);

    if (is_sorted(A, length)) {
        printf("Tablica zostala posortowana prawidlowo.");
    } else {
        printf("Tablica zostala posortowana blednie.");
    }

    return 0;
}
