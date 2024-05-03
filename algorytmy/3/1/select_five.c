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
    swap++;
    int temp = *a;
    *a = *b;
    *b = temp;
}



int partition(int A[], int lo, int hi) {
    int pivot = A[lo];
    int i = lo - 1;
    int j = hi + 1;

    while (true) {
        do {
            i++;
        } while(A[i] < pivot);

        do {
            j--;
        } while (pivot < A[j]);

        if (i >= j) {
            return j;
        }

        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
}


void sort(int A[], int lo, int hi ) {
    if (lo >=0 && hi >= 0 && lo < hi) {
        int p = partition(A, lo, hi);

        sort(A, lo, p );
        sort(A, p + 1, hi);
    }
 }

int partition_diff(int A[], int p, int r, int x) {
    int i = -1;
    for (int j = p; j < r; j++) {
        if (A[j] == x){
            i = j;
            break;
        }
    }

    if (i != -1) {
        exchange(&A[r-1], &A[i]);
    }

    int store_index = p;

    for (int j = p; j < r - 1; j++) {
        if (A[j] < x){
            int t = A[j];
            A[j] = A[store_index];
            A[store_index] = t;
            store_index++;
        }
    }

    if (i != -1) {
        exchange(&A[r-1], &A[store_index]);
    }

    return store_index;
}



int select_algorithm(int A[], int p, int r, int ind, int length) {

     // podział na grupy 
     int n = r - p + 1;
     int number_of_groups = n / 5;

     if ( n % 5 != 0) {
         number_of_groups++;
     }

    printf("Liczba grup: %d\n", number_of_groups);

     int tab[number_of_groups][5];
     printf("wielkosc: %d\n", length);

     int k = 1;
     for (int i = 0; i < number_of_groups; i++) {

         //printf("Numer grupy: %d\n", i);

         for (int j = 0; j < 5; j++) {

             if (k > length) {
                 break;
             }

             tab[i][j] = A[k];
             k++;
             //printf("%d ", tab[i][j]);
         }
         //printf("\n");
     }

    // szukam mediany
    k = 1;
    int medians[number_of_groups];
    for (int i = 0; i < number_of_groups; i++) {

        int to_sort[5];
        printf("Numer grupy: %d. W grupie: ", i);

        for (int j = 0; j < 5; j++) {
            if (k > length) {
                //k--;
                break;
            }

            to_sort[j] = tab[i][j];
            printf("%d ", to_sort[j]);
            k++;
        }

        int size_of_a_group;
        if ((k-1)%5 == 0) {
            size_of_a_group = 5;
        } else {
            size_of_a_group = (k-1) % 5;
        }
        printf("Wielosc grupy: %d\n", size_of_a_group);

        sort(to_sort, 0, size_of_a_group - 1);

        for (int x = 0; x < size_of_a_group; x++) {
            printf("%d ", to_sort[x]);
        }

        int median = to_sort[size_of_a_group/2];
        printf("mediana: %d \n", median);
        medians[i] = median;
    }

    for (int i = 0; i < number_of_groups; i++) {
        printf("%d ", medians[i]);
    }

    printf("\n");

    // mediana median 
    int median_of_medians;
    if (number_of_groups == 1) {
        median_of_medians = medians[0];
    } else { 
        median_of_medians = select_algorithm(medians, 0, number_of_groups - 1, (number_of_groups - 2) / 2, number_of_groups );
    }
    
    int index = partition_diff(A, p, r, median_of_medians);
    int m = index - p + 1;

    printf("Index: %d \n", index);

    if (ind < m) {
        return select_algorithm(A, p, index - 1, ind, ind - index + 1);
    } else if (ind > m) {
        return select_algorithm(A, index + 1, r, ind - m , r - index - 1);
    } else {
        return A[index];
    }
}

bool is_ok(int A[], int stat, int value) {
    if (A[stat] == value) {
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

    int A[length+1];
    int Init[length+1];

    for (int i = 1; i < length+1; i++) {
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

    //właściwy algorytm
    int value = select_algorithm(A, 1, length, stat, length); //czy jest git??

    if (should_print) {
        printf("Tablica poczatkowa:\n");
        for (int k = 1; k < length+1; k++) {
            if(Init[k]/10 < 1) {
                printf("0%d ", Init[k]);
            } else {
                printf("%d ", Init[k]);
            }
        }
        printf("\n");

        printf("Tablica po znalezieniu statystyki:\n");
        for (int k = 1; k < length+1; k++) {
            if(A[k]/10 < 1) {
                printf("0%d ", A[k]);
            } else {
                printf("%d ", A[k]);
            }
        }
        printf("\n");

        printf("Znalezniona statystyka: %d\n", value);

        printf("Posortowana tablica:\n");
        sort(A, 1, length);
        for (int k = 1; k < length+1; k++) {
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
