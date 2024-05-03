#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/random.h>
#include <time.h>

int comp = 0;
int swap = 0;
bool should_print = false;
int n = 0;


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

int partition(int arr[], int p, int q, int pivot) {
  //znajdujemy indeks pivota (bo przy tablicy median go utraciliśmy)
  int pivotIndex;
  for(int i = p; i <= q; i++) {
    if(is_equal(pivot, arr[i])) {
      pivotIndex = i;
      break;
    }
  }
  if(pivotIndex != p)
    exchange(&arr[pivotIndex], &arr[p]);
  pivotIndex = p;
  int j = p;
  for(int i = p+1; i <= q; i++) {
    if(is_less(arr[i], arr[pivotIndex])) {
      j++;
      exchange(&arr[j], &arr[i]);
    }
  }
  exchange(&arr[j], &arr[p]);
  return j;
}


int select_algorithm(int arr[], int p, int q, int i) {
     if (p == q){
    return arr[p];
  }
  //zadeklarowanie tablicy median o rozmiarze sufit z rozmiaru tablicy przez 5
  int medianTabSize = ( ((q-p+1)%5 == 0) ? ((q-p+1)/5): (((q-p+1)/5)+1) );
  int medianTab[medianTabSize];
  int index = 0;
  for(int i = p; i <= q; i += 5) {
    if(i + 4 <= q) {
      insertion_sort(arr, i, i+4);
      medianTab[index] = arr[i+2];
      index++;
    }
    else {
      insertion_sort(arr, i, q);
      medianTab[index] = arr[i + ((q-i)/2)];
    }
  }
  int medianOfMedian = select_algorithm(medianTab, 0, medianTabSize-1, ((medianTabSize + 1)/2));
  int r = partition(arr, p, q, medianOfMedian);
  int k = r - p + 1;
  
  if (k == i) return arr[r];
  else if (i < k) return select_algorithm(arr, p, r-1, i);
  else return select_algorithm(arr, r+1, q, i-k);
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


    //właściwy algorytm
    int value = select_algorithm(A, 0, length - 1, stat); //czy jest git??

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
