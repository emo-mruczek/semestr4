#include <stdlib.h>
#include <stdio.h>
#include <sys/random.h>
#include <string.h>
#include <time.h>



int main(int argc, char *argv[]) {
    int length = atoi(argv[1]);
    int tab[length];
    srandom(time(NULL));
    int max = 2 * length + 1;

    for (int i = 0; i < length; i++) {
        tab[i] = (random() % (max));
    }

    printf("%d\n", length);
    for (int i = 0; i < length; i++) {
        printf("%d\n", tab[i]);
    }

    return 0;
}
