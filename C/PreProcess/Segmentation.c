#include<stdio.h>
#include "../Tools.h"

/*void RemoveLittleNoise(struct Matrix matrix)
{
    for(int i = 0; i < matrix.rows ; i++)
    {
        for(int j = 0; j < matrix.columns ; j++)
        {
            if(MovePointerInMatrix(matrix, i, j) == 1)
            {
                //check si il y a un 1 autour, si non, alors on passe cette val a 0
            }
        }
    }
}*/


void HorizontalProjection(struct Matrix matrix, int* pList)
{
    int sum;
    int *p = pList;

    for(int i = 0; i < matrix.rows; i++)
    {
        sum = 0;
        for(int j = 0; j < matrix.columns; j++)
        {
            if(MovePointerInMatrix(matrix, i, j) == 1.0)
            {
                sum+=1;
            }
        }
        *p = sum;
        p++;
    }
}


void VerticalProjection(struct Matrix matrix, int* pList)
{
    int sum;
    int *p = pList;

    for(int i = 0; i < matrix.columns; i++)
    {
        sum = 0;
        for(int j = 0; j < matrix.rows; j++)
        {
            if(MovePointerInMatrix(matrix, i, j) == 1.0)
            {
                sum+=1;
            }
        }
        *p = sum;
        p++;
    }
}


int LigneSize(int *pProjH, int lenList)
{
    int res = 0;
    int isFound = 0;
    int onSpree = 0;
    int i = 0;

    while(i < lenList && isFound == 0)
    {
        if(onSpree == 0 && *pProjH != 0)
        {
            onSpree = 1;
            res++;
        }
        else if (onSpree == 1 && *pProjH != 0)
        {
            res++;
        }
        else if (onSpree == 1 && *pProjH == 0)
        {
            isFound = 1;
        }
        i++;
    }
    return res;
}


int main()
{
    struct Matrix matrix = CreateMatrix(2,2);
    ChangeEltInMatrix(matrix, 0,1,1);
    PrintMatrix(matrix);
    printf("\n");

    int *pProjH = malloc(sizeof(int)*matrix.rows);
    int *pProjH = malloc(sizeof(int)*matrix.columns);
}