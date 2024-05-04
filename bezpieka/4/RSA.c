#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

bool checkprime(uint16_t n) {
    uint16_t i, j;
    j = sqrt(n);

    for (i = 2; i <= j; i++) {
        if (n % i == 0) {
            return false;
        }
    }

    return true;
    
}



int main() {

    uint16_t prime1, prime2;

    printf("First prime number: \n");
    scanf("%hu", &prime1);

    printf("Second prime number: \n");
    scanf("%hu", &prime2);

    if (!checkprime(prime1) || !checkprime(prime2)) {
        printf("Numbers are not prime!");
        return 0;
    }

    printf("gitgut wszystko jest pierwsze :3");


    return 0;

}
