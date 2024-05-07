#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
//#include <stdint.h>
#include <sys/random.h>
#include <time.h>
#include <inttypes.h>
#include "RSA_lib.h"

uint32_t prime1, prime2;

bool check_prime(uint32_t n) {
    uint32_t root = sqrt(n);

    for(int i = 2; i <= root; i++) {
        if(n % i == 0) {
            return false;
        }
    }

    return true;
}

// znajdz takie e, ze z euler jest coprime -> czy znajduje poprawnie?
uint32_t find_e(uint32_t euler) {
    uint32_t seed;
    getrandom(&seed, sizeof(seed), 0);
    srandom(seed);
    uint32_t e;

    do {    
        e = (2 + random() % (euler));
        if (check_prime(e) && e != prime1 && e != prime2) {
            return e;
        }
    } while(euler % e == 0);
}

// znajdz d jako modular multiplicative inverse e mod euler(n)
// tj rozwiaz rownanie e * d = 1 mod euler(n) dla niewiadomej d
uint32_t euclide(uint32_t a, uint32_t b) {
    int16_t s0 = 1, s1 = 0, t0 = 0, t1 = 1, r0 = a, r1 = b;

    while (r1 != 0) {
        int16_t q = r0 / r1;

        int16_t temp = r1;
        r1 = r0 - q * r1;
        r0 = temp;

        temp = s1;
        s1 = s0 - q * s1;
        s0 = temp;

        temp = t1;
        t1 = t0 - q * t1;
        t0 = temp;
    }

    return (s0 < 0) ? s0 + b : s0;
}

void calculate_keys(struct key_pair *priv, struct key_pair *pub) {
    uint32_t n = prime1 * prime2;
    uint32_t euler  = (prime1 - 1) * (prime2 - 1);
    uint32_t e = find_e(euler);
    uint32_t d = euclide(e, euler);
    priv->n = n;
    priv->key = d;
    pub->n = n;
    pub->key = e;
}

void insert_primes(uint32_t primea, uint32_t primeb, struct key_pair *priv, struct key_pair *pub) {
    prime1 = primea;
    prime2 = primeb;

    if (!check_prime(prime1) || !check_prime(prime2) || prime1 == prime2) {
        printf("Numbers are not prime or are the same!");
        return;
    }

    calculate_keys(priv, pub);
}
