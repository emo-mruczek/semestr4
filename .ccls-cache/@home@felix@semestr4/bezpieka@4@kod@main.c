#include "RSA_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

// from geeksforgeeks
uint64_t power(uint64_t a, uint64_t b, uint64_t n){
    if (a == 0){
        return 0;
    }
    if (b == 0) {
        return 1;
    }

    uint64_t y;
    if (b % 2 == 0) {
        y = power(a, b/2, n);
        y = (y * y) % n;
    }

    else {
        y = a % n;
        y = (y * power(a, b - 1, n) % n) % n;
    }

    return ((y % n ) % n);
}

// from geeksforgeeks (again)
uint64_t gcdExtended(uint64_t a, uint64_t b, uint64_t *x, uint64_t *y) {

 if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
 
    uint64_t x1, y1; // To store results of recursive call
    uint64_t gcd = gcdExtended(b % a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}


uint64_t find_priv(struct key_pair priv_a, struct key_pair pub_a, uint64_t *p_in) {
	uint64_t t = priv_a.key * pub_a.key - 1;
	printf("%" PRIu64 "\n", t);
	uint64_t n = priv_a.n;
	uint64_t kphi = t;
	while(t % 2 == 0) {  // nie wchodzi nigdy tutaj
		t = t >> 1;
        printf("t: %" PRIu64 "\n", t);
	}
	uint64_t a = 2;
	uint64_t k, x, r, p, q, temp1, temp2;
	while(a < 100) {
		k = t;
        //printf("k: %" PRIu64 "kphi: %" PRIu64 "/n", k, kphi );
		while(k < kphi) { //tu tez nie, bo zawsze k = kphi, czemu?
			x = power(a, k, n);
            
			if(x != 1 && x != (n-1) && power(x, 2, n) == 1) {
					p = gcdExtended(x-1, n, &temp1, &temp2);
					}
					k = k*2;
		}
					a = a+2;
					}
		q = n / p;
        *p_in = p; 
		return q;
}


uint32_t euclide_test(uint32_t a, uint32_t b) {
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


uint64_t crack(uint64_t p, uint64_t q, uint64_t e) {
    uint64_t n = p * q;
    uint64_t euler = (p - 1) * (q - 1);
    uint64_t d = euclide_test(e, euler);
    return d;
}

int main() {
    uint64_t prime1 = 37;
    uint64_t prime2 = 53;

    struct key_pair pub_a;
    struct key_pair pub_b;
    struct key_pair priv_a;
    struct key_pair priv_b;

    insert_primes(prime1, prime2, &priv_a, &pub_a);
    insert_primes(prime1, prime2, &priv_b, &pub_b);

    
    printf("Your keys A: {key}, {n} \n");
    printf("Public: %" PRIu64 ", %" PRIu64 "\n", pub_a.key, pub_a.n);
    printf("Private: %" PRIu64 ", %" PRIu64 "\n", priv_a.key, priv_a.n);

    
    printf("Your keys B: {key}, {n} \n");
    printf("Public: %" PRIu64 ", %" PRIu64 "\n", pub_b.key, pub_b.n);
    printf("Private: %" PRIu64 ", %" PRIu64 "\n", priv_b.key, priv_b.n);

    printf("I have only pub_a, priv_a, pub_b.\n I'm looking for priv_b...\n");
    uint64_t p, q;
    q = find_priv(priv_a, pub_a, &p);
    printf("I've found: %" PRIu64 " as p and %" PRIu64 " as q\n", p, q);
    
    uint64_t dupa = crack(p, q, pub_b.key);
    printf("DUPA: %" PRIu64 "\n", dupa);
  /*  if(found_key == priv_b.key) {
	    printf(" - it's correct!\n");
	} else {
		printf(" - it's not correct :(\n");
	}*/

    return 0;
}
