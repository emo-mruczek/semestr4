//https://stackoverflow.com/questions/4337217/difference-between-signed-unsigned-char 
#include <string.h>
#include <stdlib.h>

#include "rc4.h"

#define LENGTH 256

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

// key-scheduling algorithm do inicjalizacji permutacji tablicy S
void ksa(unsigned char *S, char *key) {
    size_t keylength = strlen(key);

    for (int i = 0; i < LENGTH; i++) {
        S[i] = i;
    }

    int j = 0;
    for (int i = 0; i < LENGTH; i++) {
        j = (j + S[i] + key[i % keylength]) % LENGTH;
        swap(&S[i], &S[j]);
    }
}

// pseudo-random generation algorithm
void rpga(unsigned char *S, char *input, char* output) {
    int i = 0;
    int j = 0;
    int index = 0;
    int k = 0;
    size_t len = strlen(input);

    for (int n = 0; n < len; n++ ) {
        i = (i + 1) % LENGTH;
        j = (S[i] + j) % LENGTH;
        swap(&S[i], &S[j]);
        index = (S[i] + S[j]) % LENGTH;
        k = S[index];
        output[n] = k ^ input[n]; // XOR
    }
}

void encode_rc4(char *input, unsigned char *output, char *key) {
    unsigned char *S = (unsigned char*)malloc(LENGTH);

    ksa(S, key);
    rpga(S, input, output);
}
    