#ifndef _LIBREC_H
#define _LIBREC_H

struct solutionRec {
    int x;
    int y;
    int comment;
};

long factorialRec(int n);

int gcdRec(int a, int b);

struct solutionRec diofRec(int a, int b, int c);

int gcdExtendedRec(int a, int b, int* x, int* y);

#endif