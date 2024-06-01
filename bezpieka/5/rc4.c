//https://stackoverflow.com/questions/4337217/difference-between-signed-unsigned-char 
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/random.h>
#include <time.h>
#include <math.h>
#include <inttypes.h>

#include "rc4.h"

#define LENGTH 256
#define NBR 26
#define BANK 8

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
void rpga(unsigned char *S, char *input, unsigned char *output) {
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

void decode_rc4(unsigned char *input, char *output, char *key) {
    unsigned char *S = (unsigned char*)malloc(LENGTH);

    ksa(S, key);
    rpga(S, (char *)input, (unsigned char *)output);
}

// strlen unsigned char?
// 0x80 -> most significant bit
bool is_same_key(unsigned char *input1, unsigned char *input2) {
    size_t len1 = strlen((char *)input1);
    size_t len2 = strlen((char *)input2);
    size_t len = (len1 < len2) ? len1 : len2;

    for (int i = 0; i < len; i++) {
        unsigned char test = input1[i] ^ input2[i];
        printf("%02hhX\n", test);
        if (test >= 0x80) {
            return false;
        }
    }
    return true;
}

// NRB - unikatowy, 26 cyfr
// 2 - liczba kontrolna
// 8 - numer rozliczeniowy
// 16 - numer porzadkowy
// nr rozliczeniowe: https://bankoweabc.pl/numery-rozliczeniowe-bankow-w-polsce/
// wyliczanie liczby kontrolnej: https://bankoweabc.pl/2021/05/05/cyfry-w-numerze-rachunku-bankowego/
//
// https://pl.wikipedia.org/wiki/Numeracja_rachunku_bankowego
void generate_nbr(char *number, char *generated_nbr) {
    generated_nbr[26] = '\0';
    generated_nbr[0] = 0;
    generated_nbr[1] = 0;

    // kopiowanie numeru banku
    for (int i = 2, j = 0; i < 10; i++, j++) {
        generated_nbr[i] = number[j];
    }

    //generating random number
    unsigned int seed;
    getrandom(&seed, sizeof(seed), 0);
    srandom(seed);
    for (int i = 10; i < 26; i++) {
        generated_nbr[i] = (random() % (10));
    }


    //obliczanie liczby kontrolnej
    uint64_t ctrl = 0;
    uint64_t pow_ten = 1;

    for (int j = 25; j >= 0; j--) {
        printf("%d\n", generated_nbr[j]);
        ctrl += generated_nbr[j] * (pow_ten);
        pow_ten *= 10;
    }

    uint64_t pl = 2521; //numer dla kodu kraju polski
    ctrl += pl;

    printf("Suma kontrolna: %" PRIu64 "\n", ctrl);
}
