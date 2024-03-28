#ifndef _LIBLOOP_H
#define _LIBLOOP_H

struct solutionLoop {
    int x;
    int y;
    int comment;
};

long factorialLoop (int n);

int gcdLoop(int a, int b);

struct solutionLoop diofLoop(int a, int b, int c);

int gcdExtendedLoop(int a, int b, int* x, int* y);

#endif