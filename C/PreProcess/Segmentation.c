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
            if(MovePointerInMatrix(matrix, j, i) == 1.0)
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
    int *p;
    p = pProjH;

    while(i < lenList && isFound == 0)
    {
        if(onSpree == 0 && *p != 0)
        {
            onSpree = 1;
            res++;
        }
        else if (onSpree == 1 && *p != 0)
        {   
            res++;
        }
        else if (onSpree == 1 && *p == 0)
        {
            isFound = 1;
        }
        i++;
        p++;
    }
    return res;
}





int main()
{
    struct Matrix matrix = CreateMatrix(2,3);
    ChangeEltInMatrix(matrix, 0,1,1);
    ChangeEltInMatrix(matrix, 1,2,1);
    ChangeEltInMatrix(matrix, 1,1,1);
    PrintMatrix(matrix);
    printf("\n");

    int *pProjH = malloc(sizeof(int)*matrix.rows);
    int *pProjV = malloc(sizeof(int)*matrix.columns);

    int *p;
    //TEST HorizontalProj
    HorizontalProjection(matrix, pProjH);
    p = pProjH;
    for(int i = 0 ; i < matrix.rows;i++)
    {
        printf("%i\n", *p);
        p++;
    }
    printf("\n");

    //TEST VerticalProj
    VerticalProjection(matrix, pProjV);
    p = pProjV;
    for(int i = 0 ; i < matrix.columns;i++)
    {
        printf("%i\n", *p);
        p++;
    }
    printf("\n");

    //TEST LigneSize
    printf("Ligne size = %i\n", LigneSize(pProjH, matrix.rows));



}