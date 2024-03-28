#ifndef _WRAPPER_H
#define _WRAPPER_H

int gcdLoop(int a, int b);

int factorialLoop(int n);

struct solutionLoop {
    int x;
    int y;
    int comment;
};

struct solutionLoop diofLoop(int a, int b, int c);



int factorialRec(int n);

int gcdRec(int a, int b);

struct solutionRec {
    int x;
    int y;
    int comment;
};

struct solutionRec diofRec(int a, int b, int c);

#endif
