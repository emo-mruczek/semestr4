#include <stdio.h>
#include "libloop.h"

long factorialLoop(int n) {
    long result = 1;
    for (int i  = 1; i < n+1; i++) {
        result *= i;
    }
    return result;
}

int gcdLoop(int a, int b) {
    //changing negative to positive
   // a = ( a > 0) ? a : -a;
   // b = ( b > 0) ? b : -b;

   if (a < 0 ) {
    a = -a;
   }
   if (b < 0) {
    b = -b;
   }
   
   //check wether it works correctly cuz i have no idea
    while(a!=b)
    {
        if(a > b)
            a -= b;
        else
            //a -= b;
            b -= a;
    }
    return a;
}

struct solutionLoop diofLoop(int a, int b, int c) {
    struct solutionLoop result;
    int d = gcdLoop(a, b);

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
    
    float gcd = gcdExtendedLoop(gcda, gcdb, &x, &y);

    result.x = x * gcdc;
    result.y = y * gcdc;
    result.comment = "Solution exist";

    return result;
}

//for finding diofphantic equation solution
int gcdExtendedLoop(int a, int b, int* x, int* y)
{
    int x1 = 0, y1 = 1, x_curr = 1, y_curr = 0;
 
    while (a != 0) {
        int quotient = b / a;
 
        int temp_x = x_curr - quotient * x1;
        int temp_y = y_curr - quotient * y1;
 
        x_curr = x1;
        y_curr = y1;
        x1 = temp_x;
        y1 = temp_y;
 
        int temp = a;
        a = b % a;
        b = temp;
    }
 
    *x = x_curr;
    *y = y_curr;
 
    return b;
}
