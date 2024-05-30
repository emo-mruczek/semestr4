#include <stdlib.h>
#include <stdio.h>
#include <sys/random.h>
#include <time.h>

void shuffle(int *array, size_t n) {
    if (n > 1) {
        size_t i;

        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Podaj wielkosc tablicy do wygenerowania");
    }

    int length = atoi(argv[1]);
    int tab[length];
    unsigned int seed;
    getrandom(&seed, sizeof(seed), 0);
    srandom(seed);

    int max = 2 * length - 1;

    for (int i = 0; i < length; i++) {
        tab[i] = (random() % (max + 1));
    }

    for (int i = 0; i < length; i++) {
        printf("i\n");
        printf("%d\n", tab[i]);
    }

    // shuffle
    shuffle(tab, length);

    // deleting
    for (int i = 0; i < length; i++) {
        printf("d\n");
        printf("%d\n", tab[i]);
    }

    printf("e\n");

    return 0;
}
