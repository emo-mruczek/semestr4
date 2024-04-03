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

void exchange(int* a, int* b) {
    swap++;
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion(int A[], int left, int right) {
		for (int i = left + 1; i <= right; ++i) {
			int j = i-1;
            int v = A[i];
			while (v < A[j]) {
				A[j+1] = A[j];	--j;
				if (j < left) break;
			}
			A[j+1] = v;
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

int extendWeaklyLeft(int A[], int i, int left) {

    while (i > left && A[i-1] <= A[i]) --i;
        return i;


}

int extendWeaklyRight(int A[], int i, int right) {
    while (i < right && A[i+1] >= A[i]) ++i;
        return i;
    }

void peeksort(int A[], int left, int right, int left_end, int right_start, int B[]) {
    if (left_end == right || right_start == left) {
        return;
    }

    if (right - left + 1 <= INSERTION ) {
        insertion(A, left, right);
        return;
    }

    int mid = left + ((right - left) >> 1);

    if (mid <= left_end) {
        peeksort(A, left_end+1, right, left_end+1,right_start, B);
        merge(A, left, left_end+1, right, B);

    } else if (mid >= right_start) {
        peeksort(A, left, right_start-1, left_end, right_start-1, B);
        merge(A, left, right_start, right, B);

    } else {
       int i = extendWeaklyLeft(A, mid, left == left_end ? left : left_end+1);
		int j = extendWeaklyRight(A, mid, right == right_start ? right : right_start-1) ;

        if (i == left && j == right) return;
        if (mid - i < j - mid) {
            peeksort(A, left, i-1, left_end, i-1, B);
            peeksort(A, i, right, j, right_start, B);
            merge(A,left, i, right, B);

        } else {
                peeksort(A, left, j, left_end, i, B);
                peeksort(A, j+1, right, j+1, right_start, B);
                merge(A,left, j+1, right, B);
        }
    }
}

void sort(int A[], int left, int right, bool should_print) {
    int n = right - left + 1;
    int B[n];
    peeksort(A, left, right, left, right, B);
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

    printf("Łączna liczba porównan między kluczami: %d\n", comp);
    printf("Łączna liczba przestawień kluczy: %d\n", swap);

      if (is_sorted(A, length)) {
        printf("Tablica zostala posortowana prawidlowo.");
    } else {
        printf("Tablica zostala posortowana blednie.");
    }

    return 0;
}
