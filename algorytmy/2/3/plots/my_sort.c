#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int comp = 0;
int swap = 0;

#define INSERTION 10

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

void insertion(int A[], int left, int right, bool should_print) {
        for (int i = left + 1; i <= right; ++i) {
            int j = i-1;
            int v = A[i];
            while (v < A[j]) {
                A[j+1] = A[j]; --j;
                if (j < left) break;
            }
            A[j+1] = v;

             if (should_print) {
                    for (int k = 0; k <= right; k++) {
                    printf(" %d", A[k]);

                    }
                printf("\n");
            }
        }
    }

void merge(int A[], int lo, int mid, int hi, int B[]) {
    mid--;
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

int find_run_left(int A[], int i, int left) {
    while (i > left && is_less_equal(A[i-1], A[i], true)) {
       --i;
    }
        return i;
}

int find_run_right(int A[], int i, int right) {
    while (i < right && is_less_equal(A[i], A[i+1], true)) {
        ++i;
    }
        return i;
    }


void my_sort(int A[], int left, int right, int left_end, int right_start, int B[], bool should_print) {
    if (left_end == right || right_start == left) {
        return;
    }

    if (right - left + 1 <= INSERTION ) {
        insertion(A, left, right, should_print);
        return;
    }

    int mid = left + ((right - left) / 2);

    if (mid <= left_end) {
        my_sort(A, left_end+1, right, left_end+1,right_start, B,should_print);
        merge(A, left, left_end+1, right, B);

         if (should_print) {
                    for (int k = 0; k <= right; k++) {
                    printf(" %d", A[k]);

                    }
                printf("\n");
        }


    } else if (mid >= right_start) {
        my_sort(A, left, right_start-1, left_end, right_start-1, B, should_print);
        merge(A, left, right_start, right, B);

        if (should_print) {
                    for (int k = 0; k <= right; k++) {
                    printf(" %d", A[k]);

                    }
                printf("\n");
        }
    } else {
        int i, j;

        if (left == left_end) {
            i = find_run_left(A, mid, left);
        } else {
            i = find_run_left(A, mid, left_end+1);
        }

        if (right == right_start) {
            j = find_run_right(A, mid, right);
        } else {
            j = find_run_right(A, mid, right_start-1);
        }

        if (i == left && j == right) {
           return;
        }

        if (mid - i < j - mid) {
            my_sort(A, left, i-1, left_end, i-1, B, should_print);
            my_sort(A, i, right, j, right_start, B, should_print);
            merge(A,left, i, right, B);

             if (should_print) {
                for (int k = 0; k <= right; k++) {
                printf(" %d", A[k]);
                }
            printf("\n");
            }

        } else {
                my_sort(A, left, j, left_end, i, B, should_print);
                my_sort(A, j+1, right, j+1, right_start, B, should_print);
                merge(A,left, j+1, right, B);

                 if (should_print) {
                    for (int k = 0; k <= right; k++) {
                    printf(" %d", A[k]);

                    }
                printf("\n");
                }
        }
    }
}

void sort(int A[], int left, int right, bool should_print) {
    int n = right - left + 1;
    int B[n];
    my_sort(A, left, right, left, right, B, should_print);
}

bool is_sorted(int A[], int length) {
    for (int i = 0; i < length - 1; i++) {
        if (!is_less(A[i], A[i + 1], false)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
   // printf("Podaj dlugosc tablicy: ");
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

 /*   if (length < 40) {
        should_print = true;
    }
    */

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
    sort(A, 0, length - 1, should_print);

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

 /*   printf("Łączna liczba porównan między kluczami: %d\n", comp);
    printf("Łączna liczba przestawień kluczy: %d\n", swap);

      if (is_sorted(A, length)) {
        printf("Tablica zostala posortowana prawidlowo.");
    } else {
        printf("Tablica zostala posortowana blednie.");
    }*/
 printf("%d %d ", comp, swap);

    return 0;
}
