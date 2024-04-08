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


void merge(int A[], int B[], int lo, int mid, int hi) {
    for (int k = lo; k <= hi; k++) {
        B[k] = A[k];
    }

    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        if (i > mid) {
            A[k] = B[j++];
        } else if (j > hi) {
            A[k] = B[i++];
        } else if (is_less(B[j], B[i], true)) {
            A[k] = A[j++];
        } else {
            A[k] = A[i++];
        }
    }
}


void sort(int A[], int B[], int lo, int hi, bool should_print) {
    if (hi <= lo) {
        return;
    }

    int mid = lo + (hi - lo) / 2;
    sort(A, B, lo, mid, should_print);
    sort(A, B, mid + 1, hi, should_print);
    merge(A, B, lo, mid, hi);

     if (should_print) {
          for (int k = 0; k <= hi; k++) {
                printf(" %d", A[k]);

          }
          printf("\n");
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
                printf(" %d", A[l]);
                Init[l] = A[k];
        }
        printf("\n");
        printf("Kluczowe momenty:\n");
    }

    //właściwy algorytm
    int B[length];
    sort(A, B, 0, length - 1, should_print);

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

