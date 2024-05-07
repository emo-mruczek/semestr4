#include "RSA_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

// from geeksforgeeks
uint64_t power(uint64_t a, uint64_t b, uint64_t n){
	  // Initialize answer
    uint64_t res = 1;
 
    // Check till the number becomes zero
    while (b > 0) {
 
        // If y is odd, multiply x with result
        if (b % 2 == 1)
            res = (res * a);
 
        // y = y/2
        b = b >> 1;
 
        // Change x to x^2
        a = (a * a);
    }
    return res % n;
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


uint64_t find_priv(struct key_pair priv_a, struct key_pair pub_a, struct key_pair pub_b) {
	uint64_t kphi = priv_a.key * pub_a.key - 1;
	printf("%" PRIu64 "\n", kphi);
	uint64_t n = priv_a.n;
	uint64_t t = kphi;
	while(t % 2 == 0) {  // nie wchodzi nigdy tutaj
		t = t/2;
        printf("t: %" PRIu64 "\n", t);
	}
	uint64_t a = 2;
	uint64_t k, x, r, p, q, temp1, temp2;
	while(true) {
		k = t;
        //printf("k: %" PRIu64 "kphi: %" PRIu64 "/n", k, kphi );
		while(k < kphi) { //tu tez nie, bo zawsze k = kphi, czemu?
			x = power(a, k, n);
            
			if(x != 1 && x != (n-1) && power(x, 2, n) == 1) {
					p = gcdExtended(x-1, n, &temp1, &temp2);
					break;
					}
					k = k*2;
		}
					a = a+2;
					}
		q = n / p;
		return q;
}





int main() {
    uint64_t prime1 = 1234567891;
    uint64_t prime2 = 1234577;

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

    uint64_t found_key = find_priv(priv_a, pub_a, pub_b);
    printf("I've found: %" PRIu64, found_key);

    if(found_key == priv_b.key) {
	    printf(" - it's correct!\n");
	} else {
		printf(" - it's not correct :(\n");
	}

    return 0;
}
