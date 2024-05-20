#ifndef _RSA_LIB_H_
#define _RSA_LIB_H_

#include <stdint.h>
#include <inttypes.h>

struct key_pair {
    uint32_t n;
    uint32_t key;
};

void insert_primes(uint32_t primea, uint32_t primeb, struct key_pair *priv, struct key_pair *pub);

#endif
