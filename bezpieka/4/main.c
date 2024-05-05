#include "RSA_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

int main() {
    uint32_t prime1 = 1234567891;
    uint32_t prime2 = 1234577;

    struct key_pair pub_a;
    struct key_pair pub_b;
    struct key_pair priv_a;
    struct key_pair priv_b;

    insert_primes(prime1, prime2, &priv_a, &pub_a);
    insert_primes(prime1, prime2, &priv_b, &pub_b);

    
    printf("Your keys A: {key}, {n} \n");
    printf("Public: %" PRIu32 ", %" PRIu32 "\n", pub_a.key, pub_a.n);
    printf("Private: %" PRIu32 ", %" PRIu32 "\n", priv_a.key, priv_a.n);

    
    printf("Your keys B: {key}, {n} \n");
    printf("Public: %" PRIu32 ", %" PRIu32 "\n", pub_b.key, pub_b.n);
    printf("Private: %" PRIu32 ", %" PRIu32 "\n", priv_b.key, priv_b.n);

    return 0;
}
