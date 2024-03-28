#include <stdio.h>
#include "libloop.h"
#include "librec.h"

int main() {
    long fac = factorialLoop(5);
    int gcd = gcdLoop(10, 5);
    struct solutionLoop diofL = diofLoop(1027, 712, 1);

    printf("For loop implementation:\na) %ld \nb) %d \nc) %f oraz %f (%s)\n", fac, gcd, diofL.x, diofL.y, diofL.comment);

    fac = factorialRec(5);
    gcd = gcdRec(10, 5);
    struct solutionRec diofR = diofRec(1027, 712, 1);

    printf("For recursive implementation:\na) %ld \nb) %d \nc) %f oraz %f (%s)\n", fac, gcd, diofR.x, diofR.y, diofR.comment);


    return 0;
}