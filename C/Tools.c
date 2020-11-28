#include<stdlib.h>
#include<stdio.h>
#include "Tools.h"

//AUTHOR: Alexandre GAUTIER

void PrintList(int);

//##### Creation of Matrix #####
struct Matrix CreateMatrix(int rows, int columns)
{
    struct Matrix matrix;

    matrix.rows = rows;
    matrix.columns = columns;

    //TODO: Peut être passer en calloc
    matrix.pmatrix = malloc(sizeof(double)*columns*rows);

    return matrix;
}


//##### Verification #####

//check if x,y is in in bound
int IsInMatrix(struct Matrix matrix, int x, int y)
{
    return(x < matrix.rows, matrix.columns);
}


//##### Changes in Matrix #####

//navigate in the flatten matrix and return the pointer to the elt in x,y if it exist
double MovePointerInMatrix(struct Matrix matrix, int x, int y)
{
    if (!IsInMatrix(matrix, x, y))
    {
        printf("ERROR: Coordonates invalid in the matrix");
    }
    int indexOfElt = x * matrix.columns + y;
    return *(matrix.pmatrix + indexOfElt);

}

//change an elt in the matrix
void ChangeEltInMatrix(struct Matrix matrix, int x, int y, double val)
{
    if (!IsInMatrix(matrix, x, y))
    {
        printf("ERROR: Coordonates invalid in the matrix");
    }
    int indexOfElt = x * matrix.columns + y;
    *(matrix.pmatrix + indexOfElt) = val;
}


//##### PRINTS #####

//Print the element in (x,y) in the matrix
void PrintEltIntMatrix(struct Matrix matrix, int x, int y)
{
    printf("Element in (%i, %i) = %f\n", x, y, MovePointerInMatrix(matrix, x, y));
}

//Print all elt in matrix
void PrintMatrix(struct Matrix matrix)
{
    for(int i = 0; i < matrix.rows; i++)
    {
        for(int j = 0; j < matrix.columns; j++)
        {
            printf("%f ", MovePointerInMatrix(matrix, i, j));
        }
        printf("\n");
    }
}


//##### Initialisation #####

//Initialise all the matrix with zeros
void InitialiseMatrixWithZero(struct Matrix matrix)
{
    for(int i = 0; i < matrix.rows; i++)
    {
        for(int j = 0; j < matrix.columns; j++)
        {
            ChangeEltInMatrix(matrix, i, j, 0);
        }
    }
}

/*
//##### TESTS #####
int main() {
    struct Matrix matrix = CreateMatrix(3,3);
    InitialiseMatrixWithZero(matrix);

    PrintMatrix(matrix);
    printf("###############\n");

    ChangeEltInMatrix(matrix, 0, 2, 3);
    PrintMatrix(matrix);
    printf("###############\n");

    printf("%f", MovePointerInMatrix(matrix, 0, 2));
    printf("\n");
    printf("###############\n");

    free(matrix.pmatrix);
    return 0;
}*/