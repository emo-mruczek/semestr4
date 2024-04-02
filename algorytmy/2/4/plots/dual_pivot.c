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

// is from 0 to p more keys than from q to A.length?
bool is_more_p(int A[], int p, int q, int len) {
    int cp, cq = 0;
    for (int i = 0; i < p; i++) {
        cp++;
    }
    for(int i = q+1; i < len; i++) {
        cq++;
    }

    if (cp >- cq){
        return true;
    } else {
        return false;
    }
}

int partition(int A[], int p, int q, int len, int* l) {
    if (A[p] > A[q]) {
         exchange(&A[p], &A[q]);
    }
    int j = p + 1;
    int k = p + 1;
    int g = q - 1;

    while (is_less_equal(k, g, false)) {
       
          
            if (is_less(A[k], A[p], true)) {
                exchange(&A[k], &A[j]);
                j++;
            } else if (is_less_equal(A[q], A[k], true)) {
                while (is_less(A[q], A[g], true) && is_less(k, g, false)) {
                    g--;
                }
                exchange(&A[k], &A[g]);
                g--;

                if (is_less(A[k], A[p], true)) {
                     exchange(&A[k], &A[j]);
                     j++;
                }
            }
            k++;
        
            if (is_less_equal(A[q], A[k], true)) {
                while (is_less(A[q], A[g], true) && is_less(k, g, false)) {
                    g--;
                }
                exchange(&A[k], &A[g]);
                g--;

                if (is_less(A[k], A[p], true)) {
                     exchange(&A[k], &A[j]);
                     j++;
                }
            } else if (is_less(A[k], A[p], true)) {
                exchange(&A[k], &A[j]);
                j++;
            } 
            k++;    
    }
    j--;
    g++;
    
    exchange(&A[p], &A[j]);
    exchange(&A[q], &A[g]);

    *l = j;
    return g;
}




void alghoritm(int A[], int p, int q, int len, bool should_print) {
    if (p < q) {

        if(should_print) {
            for (int k = 0; k < q+1; k++) {
                printf(" %d", A[k]);
            }
            printf("\n");
        }


        int l, r;
        r = partition(A, p, q, len, &l);
        alghoritm(A, p, l - 1, len, should_print);
        alghoritm(A, l + 1, r - 1, len, should_print);
        alghoritm(A, r + 1, q, len, should_print);
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
    alghoritm(A, 0, length - 1, length, should_print);

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


