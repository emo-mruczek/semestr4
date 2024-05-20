#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CUTOFF 8

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

int insertion(int A[], int lo, int hi, bool should_print){
    int i = lo + 1;
    while (i <= hi) {
       int j = i;
       while (j > lo && is_less(A[j], A[j-1], true))  {
            exchange(&A[j], &A[j-1]);
            j--;
       }

       if (should_print) {
          for (int k = 0; k <= hi; k++) {
                printf(" %d", A[k]);
 
          }
          printf("\n");
       }

       i++;
   }
}

int partition(int A[], int lo, int hi, bool should_print) {
    int m = lo + (hi - lo) / 2;
    exchange(&A[m], &A[lo]);

    int i =  lo + 1;
    int j = hi;
    int pivot = A[lo];

    while (i <= j) {
        while (i <= hi && is_less(A[i], pivot, true))
            i++;
        while (j > lo && is_less(pivot, A[j], true))
            j--;

        if (i < j)
            exchange(&A[i++], &A[j--]);
        else
            break;
    }

    exchange(&A[lo], &A[j]);

    if (should_print) {
        for (int k = 0; k <= hi; k++) {
                printf(" %d", A[k]);
        }
            printf("\n");
    }

    return j;
}

void hybrid(int A[], int lo, int hi, bool should_print) {
    if (hi <= lo) {
        return;
    }

    int n = hi - lo + 1;
    if (n <= CUTOFF) {
        insertion(A, lo, hi, should_print);
        return;
    }

    int j = partition(A, lo, hi, should_print);
    hybrid(A, lo, j-1, should_print);
    hybrid(A, j+1, hi, should_print);
}


 bool is_sorted(int A[], int length) {
    for (int i = 0; i < length - 1; i++) {
        if (A[i] > A[i + 1]) {
            return false;
        }
    }
    return true;
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
            printf(" %d", A[k]);
            Init[k] = A[k];
        }
        printf("\n");
        printf("Kluczowe momenty:\n");
    }

    //właściwy algorytm
    hybrid(A, 0, length - 1, should_print);

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
        printf("Tablica posortowana:\n");
        for (int k = 0; k < length; k++) {
            if(A[k]/10 < 1) {
                printf("0%d ", A[k]);
            } else {
                printf("%d ", A[k]);
            }
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
