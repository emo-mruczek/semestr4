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



int select_algorithm(int A[], int p, int r, int i, int length) {

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

                      

        /*switch(size_of_a_group) {
            case 5 :
                median = to_sort[2];
                break;
            case 3 :
                median = to_sort[1];
                break;
            default:
                break;
            
        }*/
        

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
