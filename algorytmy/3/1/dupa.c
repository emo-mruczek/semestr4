#include <stdio.h>

void exchange(int *a, int *b) {
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
    for (int j = p; j < r; j++) {
        if (A[j] == x){
            i = j;
            break;
        }
    }

    if (i != p - 1) {
        exchange(&A[r-1], &A[i]);
    }

    int store_index = p;

    for (int j = p; j < r - 1; j++) {
        if (A[j] < x){
            exchange(&A[j], &A[store_index]);
            store_index++;
        }
    }

    exchange(&A[r-1], &A[store_index]);

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

int main() {
    int A[] = {7, 10, 4, 3, 20, 15};
    int n = 6;
    // dostosowuje indeks
     int ind = 1;
     int pass;
    if (ind == n) {
        pass = 1;
    } else {
        pass = ind + 1;
    }
    int result = select_algorithm(A, 0, n - 1, pass);
    printf("The %d-th smallest element is %d\n", ind, result);
    return 0;
}

