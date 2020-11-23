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


//Make an histogram with the number of 1 in each line of the binarized matrix
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


//Make an histogram with the number of 1 in each line of the binarized matrix
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


//Search for the maximum of 1 on a line of the binarized matrix = highest number on the HorizontalProjection's histogram
int maxBlackPxlOnLine(int* pProjH, int matrixNbOfRows)
{
    int *p;
    p = pProjH;
    int max = *p;

    for(int i = 1; i < matrixNbOfRows ; i++)
    {
        if(*p > max)
        {
            max = *p;
        }
    }

    return max;
}


//Return the size of the first line of texte of the matrix
int LineSize(int *pProjH, int lenList)
{
    int treshold = maxBlackPxlOnLine(pProjH, lenList)/2;
    int res = 0;
    int isFound = 0;
    int onSpree = 0;
    int i = 0;
    int *p;
    p = pProjH;

    while(i < lenList && isFound == 0)
    {
        if(onSpree == 0 && *(p+i) > treshold)
        {
            onSpree = 1;
            res++;
        }
        else if (onSpree == 1 && *(p+i) > treshold)
        {   
            res++;
        }
        else if (onSpree == 1 && *(p+i) < treshold)
        {
            isFound = 1;
        }
        i++;
    }
    return res;
}


//return the biggeest line size
/*int maxLineSize(int *pProjH, int lenList)
{
    int treshold = maxBlackPxlOnLine(pProjH, lenList)/2;
    int maxSize = 0;
    int currentSize = 0;
    int onSpree = 0;
    int *p;
    p = pProjH;

    for(int i = 0 ; i < lenList ; i++)
    {
        if(onSpree == 0 && *p > treshold)
        {
            onSpree = 1;
            currentSize++;
        }
        else if (onSpree == 1 && *p > treshold)
        {   
            currentSize++;
        }
        else if (onSpree == 1 && *p < treshold)
        {
            if (currentSize > maxSize)
            {
                maxSize = currentSize;
            }
            onSpree = 0;
            currentSize = 0;
        }
    }
}*/


//Count the total number of lines + paragraph in the text
int CountNbOfLinesAndParagraph(int matrixNbRows, int lineSize, int* pProjH)
{
    int treshold = maxBlackPxlOnLine(pProjH, matrixNbRows)/2;
    int onSpree = 0;
    int sum = 0;
    int nbNotLine = 0;
    int *p;
    p = pProjH;

    for(int i = 0 ; i < matrixNbRows ; i++)
    {
        if(onSpree == 0 && *(p+i) > treshold)
        {
            onSpree = 1;
            if(nbNotLine > lineSize*3)
            {
                sum++;
            }
            nbNotLine = 0;
        }
        else if (onSpree == 1 && *(p+i) < treshold)
        {
            sum++;
            nbNotLine++;
            onSpree = 0;
        }
        else if (onSpree == 0 && *(p+i) < treshold) 
        {
            nbNotLine++;
        }
    }

    return sum;
}


void iMatrix()
{

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
    printf("HorizontalProj\n");
    HorizontalProjection(matrix, pProjH);
    p = pProjH;
    for(int i = 0 ; i < matrix.rows;i++)
    {
        printf("%i\n", *p);
        p++;
    }
    printf("\n");

    //TEST VerticalProj
    printf("VerticalProj\n");
    VerticalProjection(matrix, pProjV);
    p = pProjV;
    for(int i = 0 ; i < matrix.columns;i++)
    {
        printf("%i\n", *p);
        p++;
    }
    printf("\n");

    //TEST LigneSize
    printf("Ligne size = %i\n", LineSize(pProjH, matrix.rows));

    //TEST iList
    int nbLines = CountNbOfLinesAndParagraph(matrix.rows, LineSize(pProjH, matrix.rows), pProjH);
    struct Matrix linesMatrix = CreateMatrix(nbLines,3);
}