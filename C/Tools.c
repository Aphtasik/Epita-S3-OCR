#include<stdlib.h>
#include "Tools.h"

struct Matrix CreateMatrix(int rows, int columns)
{
    struct Matrix matrix;

    matrix.rows = rows;
    matrix.columns = columns;

    matrix.pmatrix = malloc(sizeof(double)*columns*rows);
    if (matrix.pmatrix == NULL)
    {
        errx(1, "Not enough memory");
    }

    return matrix;
}

//check if x,y is in in bound
int IsInMatrix(struct Matrix matrix, int x, int y)
{
    return(x < matrix.rows, matrix.columns);
}

//navigate in the flatten matrix and return the element in x,y if it exist
double GetEltInMatrix(struct Matrix matrix, int x, int y)
{
    if (!IsInMatrix(matrix, x, y))
    {
        printf("ERROR: Coordonates invalid in the matrix");
    }
    int indexOfElt = x * matrix.columns + y;
    return *(matrix.pmatrix + indexOfElt);

}

void InitMatrix(struct Matrix matrix)
{
    for(int i = 0; i < matrix.rows; i++)
    {
        for(int j = 0; j < matrix.columns; j++)
        {
            printf("%f ", GetEltInMatrix(matrix, i, j));
        }
    }
}