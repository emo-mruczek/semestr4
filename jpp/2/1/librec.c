#include <stdio.h>
#include "librec.h"


long factorialRec(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorialRec(n - 1);
    }
}

int gcdRec(int a, int b) {
    a = (a > 0) ? a : -a;
    b = (b > 0) ? b : -b;

    if (a == b) {
        return a;
    } else if (a > b) {
        return gcdRec(a - b, b);
    } else {
        return gcdRec(a, b - a);
    }
}

struct solutionRec diofRec(int a, int b, int c) {
    struct solutionRec result;
    int d = gcdRec(a, b);

    if (c % d != 0) {
        result.x = 0;
        result.y = 0;
        result.comment = "Solution does not exist";
        return result;
    }

    float gcda = a / d;
    float gcdb = b / d;
    float gcdc = c / d;
    // now gcd = 1
    float x, y;
    
    float gcd = gcdExtendedRec(gcda, gcdb, &x, &y);

    result.x = x * gcdc;
    result.y = y * gcdc;
    result.comment = "Solution exist";

    return result;
}


//for finding diofphantic equation solution
int gcdExtendedRec(int a, int b, int* x, int* y)
{
    
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
 
    int x1, y1; 
    int gcd = gcdExtendedRec(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;

   return gcd;
}