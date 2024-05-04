#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <sys/random.h>
#include <time.h>

struct key_pair {
    uint16_t n;
    uint16_t key;
};

uint16_t prime1, prime2;

bool check_prime(uint16_t n) {
    if (n <= 1 ) {
        return false;
    }

    uint16_t i, j;
    j = sqrt(n);

    for (i = 2; i <= j; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

uint16_t find_e(uint16_t euler) {
    uint16_t seed;
    getrandom(&seed, sizeof(seed), 0);
    srandom(seed);
    uint16_t e;

    while(true) {    
        e = (1 + random() % (euler));

        if(euler % e == 0) {
            continue;
        } 

        if (check_prime(e) && e != prime1 && e != prime2) {
            return e;
        }
    }
}

uint16_t euclide(uint16_t n, uint16_t euler) {
    uint16_t temp;
    for (uint16_t i = 1; i < euler; i++) {
        if ((i*n) % euler == 1) {
            temp = 1;
            break;
        }
    }

    return temp;
}

void calculate_keys(struct key_pair *priv, struct key_pair *pub) {
    uint16_t n = prime1 * prime2;
    uint16_t euler  = (prime1 - 1) * (prime2 - 1);
    uint16_t e = find_e(euler);
    uint16_t d = euclide(e, euler);
    priv->n = n;
    priv->key = d;
    pub->n = n;
    pub->key = e;
}

int main() {
    printf("First prime number: \n");
    scanf("%hu", &prime1);

    printf("Second prime number: \n");
    scanf("%hu", &prime2);

    if (!check_prime(prime1) || !check_prime(prime2) || prime1 == prime2) {
        printf("Numbers are not prime or are the same!");
        return 0;
    }

    printf("gitgut wszystko jest pierwsze :3");

    struct key_pair priv, pub;
    calculate_keys(&priv, &pub);

    //printing

    printf("Your keys: {key}, {n} \n");
    printf("Public: %hu, %hu\n", pub.key, pub.n);
    printf("Private: %hu, %hu\n", priv.key, priv.n);


    return 0;
}
