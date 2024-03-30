#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int comp = 0;
int swap = 0;

int partition(int A[], int lo, int hi) {
    int pivot = A[lo];
    int i = lo - 1;
    int j = hi + 1;

    while (true) {
        do {
            i++;
            comp++;
        } while (A[i] < pivot);

        do {
            j--;
            comp++;
        } while (A[j] > pivot);

        if (i >= j) {
            return j;
        }

         // swap
            swap++;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            
    }
}


void alghoritm(int A[], int lo, int hi, bool should_print) {
    if (lo >=0 && hi >= 0 && lo < hi) {
  if(should_print) {
            for (int k = 0; k < hi+1; k++) {
                printf(" %d", A[k]);
            }
            printf("\n");
        }


        int p = partition(A, lo, hi);
        
        alghoritm(A, lo, p, should_print);
        alghoritm(A, p + 1, hi, should_print);
    }

 }

int main(int argc, char *argv[]) {
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
            printf("%d ", Init[k]);
        }
        printf("\n");
        printf("Tablica posortowana:\n");
        for (int k = 0; k < length; k++) {
            printf("%d ", A[k]);
        }
        printf("\n");
    }

    printf("%d %d ", comp, swap);

    return 0;
}
