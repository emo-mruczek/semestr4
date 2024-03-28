#include <stdio.h>
#include <stdlib.h>


struct solutionLoop {
    int x;
    int y;
    int comment;
};

struct solutionRec {
    int x;
    int y;
    int comment;
};


extern long int factorialRec(int n);
extern int gcdRec(int a, int b);
extern struct solutionRec diofRec(int a, int b, int c);
extern int gcdExtendedRec(int a, int b, int* x, int* y);
extern long int factorialLoop(int n);
extern int gcdLoop(int a, int b);
extern struct solutionLoop diofLoop(int a, int b, int c);
extern int gcdExtendedLoop(int a, int b, int* x, int* y);


int main() {
    long fac = factorialLoop(5);
    int gcd = gcdLoop(10, 5);
    struct solutionLoop diofL = diofLoop(1027, 712, 1);

    printf("For loop implementation:\na) %ld \nb) %d \nc) %d oraz %d (%d)\n", fac, gcd, diofL.x, diofL.y, diofL.comment);

    fac = factorialRec(5);
    gcd = gcdRec(10, 5);
    struct solutionRec diofR = diofRec(1027, 712, 1);

      printf("For recursive implementation:\na) %ld \nb) %d \nc) %d oraz %d (%d)\n", fac, gcd, diofR.x, diofR.y, diofR.comment);


    return 0;
}