#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int length = atoi(argv[1]);
    int tab[length];

    for (int i = 0; i < length; i++) {
        tab[i] = i + 1;
    }

    printf("%d/n", length);
    for (int i = 0; i < length; i++) {
        printf(" %d", tab[i]);
    }
    printf("/n");

    return 0;
}
