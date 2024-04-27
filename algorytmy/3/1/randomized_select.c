#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int comp = 0;
int swap = 0;
bool shoud_print = false;

bool is_less(int a, int b) {
    comp++

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


int partition(int A[], int lo, int hi) {
    int pivot = A[lo];
    int i = lo - 1;
    int j = hi + 1;

    while (true) {
        do {
            i++;
        } while(is_less(A[i], pivot, true));

        do {
            j--;
        } while (is_less(pivot, A[j], true));

        if (i >= j) {
            return j;
        }

        exchange(&A[i], &A[j]);
    }
}


void sort(int A[], int lo, int hi ) {
    if (lo >=0 && hi >= 0 && lo < hi) {
        int p = partition(A, lo, hi);
        
        sort(A, lo, p );
        sort(A, p + 1, hi);
    }
 }



int rand_partition(int A[], int p, int q) {

}


int select(int A[], int p, int q, int i) {
    if (A[p] == A[q]) {
        return p;
    }

    int r = rand_partition(A, p, q);
    int k = r - p + 1;

    if (is_equal(i, k)) {
        return A[r];
    } else if (is_less(i, k)) {
        return select(A, p, r - 1, i);
    } else {
        return select(A, r + 1, q, i - k);
    }
}

bool is_ok(int A, int stat, int value) {
    if (A[stat] == A[value]) {
        return true;
    } else {
        return false;
    }
}


int main() {
    printf("Podaj dlugosc tablicy: ");
    int length;
    scanf("%d", &length);

    printf("Podaj numer szukanej statystyki pozycyjnej");
    int stat;
    scanf("%d", &stat);

    if (stat > len || stat < 0) {
        printf("Podano nieistniejaca statystyke pozycyjna");
        return 0;
    }

    int A[length];
    int Init[length];

    for (int i = 0; i < length; i++) {
        int num;
        scanf("%d", &num);
        A[i] = num;
    }

    if (length < 50) {
        should_print = true;
    }

    if (should_print) {
        printf("\n");
        printf("Kluczowe momenty:\n");
    }
    
    //właściwy algorytm
    int value = select(A, 0, length, stat); //czy jest git??

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

        printf("Tablica po znalezieniu statystyki:\n");
        for (int k = 0; k < length; k++) {
            if(A[k]/10 < 1) {
                printf("0%d ", A[k]);
            } else {
                printf("%d ", A[k]);
            }
        }
        printf("\n");

        printf("Znalezniona statystyka: %d", value);
    
        printf("Posortowana tablica:\n");
        sort(A, 0, length - 1);
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

    if (is_ok(A, stat, value)) {
        printf("Tablica zostala posortowana prawidlowo.");
    } else {
        printf("Tablica zostala posortowana blednie.");
    }

    return 0;
}
