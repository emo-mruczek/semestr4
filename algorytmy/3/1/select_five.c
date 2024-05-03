#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/random.h>
#include <time.h>

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
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int arr[], int low, int high) {
    for (int i = low + 1; i <= high; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
int partition_diff(int A[], int p, int r, int x) {
    int i = p - 1;
    for (int j = p; j <= r; j++) {
        if (A[j] == x){
            i = j;
            break;
        }
    }

    if (i != p - 1) {
        exchange(&A[r], &A[i]);
    }

    int store_index = p;

    for (int j = p; j < r; j++) {
        if (A[j] < x){
            exchange(&A[j], &A[store_index]);
            store_index++;
        }
    }

    exchange(&A[r], &A[store_index]);

    return store_index;
}


int select_algorithm(int A[], int p, int r, int ind) {
    int n = r - p + 1;
    if (ind > 0 && ind <= n) {
        if (n <= 5) {
            insertion_sort(A, p, r);
            return A[p + ind - 1];
        }

        // Divide A[] into groups of 5 elements
        int number_of_groups = (n + 4) / 5;
        int medians[number_of_groups];

        for (int i = 0; i < number_of_groups; i++) {
            int median_index = p + 5 * i + 2;
            medians[i] = select_algorithm(A, p + 5 * i, median_index - 1, 3);
        }

        int median_of_medians = select_algorithm(medians, 0, number_of_groups - 1, number_of_groups / 2);

        int index = partition_diff(A, p, r, median_of_medians);
        int m = index - p + 1;

        if (ind < m) {
            return select_algorithm(A, p, index - 1, ind);
        } else if (ind > m) {
            return select_algorithm(A, index + 1, r, ind - m);
        } else {
            return A[index];
        }
    }
    return -1; // Out of range index
}

bool is_ok(int A[], int stat, int value) {
    if (A[stat - 1] == value) {
        return true;
    } else {
        return false;
    }
}


int main() {
    printf("Podaj dlugosc tablicy: \n");
    int length;
    scanf("%d", &length);

    printf("Podaj numer szukanej statystyki pozycyjnej: \n");
    int stat;
    scanf("%d", &stat);

    if (stat > length || stat < 1) {
        printf("Podano nieistniejaca statystyke pozycyjna");
        return 0;
    }

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

    if (should_print) {
        printf("\n");
        printf("Kluczowe momenty:\n");
    }

    int pass = stat;

    //właściwy algorytm
    int value = select_algorithm(A, 0, length - 1, pass); //czy jest git??

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

        printf("Znalezniona statystyka: %d\n", value);

        printf("Posortowana tablica:\n");
        insertion_sort(A, 0, length - 1);
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
        printf("Znaleziono prawidlowa statystyka.");
    } else {
        printf("Bledna statystyka.");
    }

    return 0;
}
