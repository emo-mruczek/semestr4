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

bool is_less_equal(int a, int b, bool count) {
    if (count) {
        comp++;
    }

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

void rotate(int* a, int* b, int* c) {
    swap += 2;
    int temp = *a;
    *a = *b;
    *b = *c;
    *c = temp;
}

int partition(int A[], int p, int q, int* ret) {
    if (is_less(A[q], A[p], true)) {
         exchange(&A[p], &A[q]);
    }

    int l = A[p];
    int r = A[q];
    int i = p + 1;
    int k = q - 1;
    int j = i;
    int d = 0; // holds difference between small and large numbers
    
    while (j <= k) {
        if (d >= 0) {
            if (is_less(A[j], l, true)) {
                exchange(&A[i], &A[j]);
                i++;
                j++;
                d++;
            } else {
                if (is_less(A[j], r, true)) {
                    j++;
                } else {
                    exchange(&A[j], &A[k]);
                    k--;
                    d--;
                }
            }
        } else {
            if (is_less(r, A[k], true)) {
                k--;
                d--;
            } else {
                if (is_less(A[k], l, true)) {
                    rotate(&A[k], &A[j], &A[i]);
                    i++;
                    d++;
                } else {
                    exchange(&A[j], &A[k]);
                }
                j++;
            }
        }
    }

    exchange(&A[p], &A[i-1]);
    exchange(&A[q], &A[k+1]);

    *ret = i;
    return k;
}


void alghoritm(int A[], int p, int q, bool should_print) {
    if (p < q) {

        if(should_print) {
            for (int k = 0; k < q+1; k++) {
                printf(" %d", A[k]);
            }
            printf("\n");
        }

        int l, r;
        r = partition(A, p, q, &l);
        alghoritm(A, p, l - 2, should_print);
        alghoritm(A, l, r, should_print);
        alghoritm(A, r + 1, q, should_print);
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
    alghoritm(A, 0, length - 1, should_print);

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


