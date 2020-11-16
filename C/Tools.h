#ifndef TOOLS_H
#define TOOLS_H

#include<stdio.h>
#include<stdlib.h>

struct Matrix
{
    int rows;
    int columns;

    double *pmatrix;
};

struct Matrix CreateMatrix(int rows, int columns);
int IsInMatrix(struct Matrix matrix, int x, int y);

#endif