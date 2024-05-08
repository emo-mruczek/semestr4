#include "RSA_lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include "bigint.h"

using namespace std;

// from geeksforgeeks
bigint power(bigint a, bigint b, bigint n){
    if (a == 0){
        return 0;
    }
    if (b == 0) {
        return 1;
    }

    bigint y;
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
bigint gcdExtended(bigint a, bigint b, bigint *x, bigint *y) {

 if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
 
    bigint x1, y1; // To store results of recursive call
    bigint gcd = gcdExtended(b % a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}


bigint find_priv(struct key_pair priv_a, struct key_pair pub_a, bigint *p_in) {
	bigint t = priv_a.key * pub_a.key - 1;
    cout << t << endl;
    //printf("%" PRIu64 "\n", t);
	bigint n = priv_a.n;
	bigint kphi = t;
	while(t % 2 == 0) {  // nie wchodzi nigdy tutaj
		t = t >> 1;
        cout << "t: " << t << endl;
        //printf("t: %" PRIu64 "\n", t);
	}
	bigint a = 2;
	bigint k, x, r, p, q, temp1, temp2;
	while(a<100) {
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


bigint euclide_test(bigint a, bigint b) {
    bigint s0 = 1, s1 = 0, t0 = 0, t1 = 1, r0 = a, r1 = b;

    while (r1 != 0) {
        bigint q = r0 / r1;

        bigint temp = r1;
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


bigint crack(bigint p, bigint q, bigint e) {
    bigint n = p * q;
    bigint euler = (p - 1) * (q - 1);
    bigint d = euclide_test(e, euler);
    return d;
}

int main() {

    bigint prime1 = 1234567891;
    bigint prime2 = 1234577;

    struct key_pair pub_a;
    struct key_pair pub_b;
    struct key_pair priv_a;
    struct key_pair priv_b;

    insert_primes(prime1, prime2, &priv_a, &pub_a);
    insert_primes(prime1, prime2, &priv_b, &pub_b);

    cout << "Your keys A: {key}, {n}" << endl;
    cout << "Public: " << pub_a.key << ", " << pub_a.n;
    cout << "Private " << priv_a.key << ", " << priv_a.n;

    cout << "Your keys B: {key}, {n}" << endl;
    cout << "Public: " << pub_b.key << ", " << pub_b.n;
    cout << "Private " << priv_b.key << ", " << priv_b.n;
 /*  printf("Your keys A: {key}, {n} \n");
    printf("Public: %" PRIu64 ", %" PRIu64 "\n", pub_a.key, pub_a.n);
    printf("Private: %" PRIu64 ", %" PRIu64 "\n", priv_a.key, priv_a.n);

    
    printf("Your keys B: {key}, {n} \n");
    printf("Public: %" PRIu64 ", %" PRIu64 "\n", pub_b.key, pub_b.n);
    printf("Private: %" PRIu64 ", %" PRIu64 "\n", priv_b.key, priv_b.n);
    */

    cout << "I have only pub_a, priv_a, pub_b. I'm looking for priv_b...\n");
    bigint p, q;
    q = find_priv(priv_a, pub_a, &p);
    cout << "I've found: " << p << " as p and " << q << " as q\n";
    
    bigint very_secret_key = crack(p, q, pub_b.key);
    cout << "Very secret key: %" << very_secret_key << endl;
    if(very_secret_key == priv_b.key) {
	    printf(" - it's correct!\n");
	} else {
		printf(" - it's not correct :(\n");
	}

    return 0;
}
