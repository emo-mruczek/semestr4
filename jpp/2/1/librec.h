#ifndef _LIBREC_H
#define _LIBREC_H

struct solutionRec {
    float x;
    float y;
    char *comment;
};

long factorialRec(int n);

int gcdRec(int a, int b);

struct solutionRec diofRec(int a, int b, int c);

int gcdExtendedRec(int a, int b, int* x, int* y);

#endif