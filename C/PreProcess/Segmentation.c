#include<stdio.h>
#include "../Tools.h"


//AUTHOR: Alexandre GAUTIER


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
        *(p+i) = sum;
    }
}


//Make an histogram with the number of 1 in each line of the binarized matrix between the rows min and max index
void VerticalProjection(struct Matrix matrix, int minIndex, int maxIndex, int* pList)
{
    int sum;
    int *p = pList;

    for(int i = 0; i < matrix.columns; i++)
    {
        sum = 0;
        for(int j = minIndex; j <= maxIndex; j++)
        {
            if(MovePointerInMatrix(matrix, j, i) == 1.0)
            {
                sum+=1;
            }
        }
        *(p+i) = sum;
    }
}


//Search for the maximum of 1 on a line or column of the binarized matrix = highest number on the Vertical/HorizontalProjection's histogram
int MaxBlackPxl(int* pProj, int matrixLen)
{
    int *p = pProj;
    int max = *p;

    for(int i = 1; i < matrixLen ; i++)
    {
        if(*(p+i) > max)
        {
            max = *(p+i);
        }
    }

    return max;
}


//Return the size of the first line of texte of the matrix
int Size(int *pProj, int lenList)
{
    int treshold = MaxBlackPxl(pProj, lenList)/2;
    int res = 0;
    int isFound = 0;
    int onSpree = 0;
    int i = 0;
    int *p = pProj;

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
    int treshold = MaxBlackPxlOnLine(pProjH, lenList)/2;
    int maxSize = 0;
    int currentSize = 0;
    int onSpree = 0;
    int *p = pProjH;

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
//Doesn't take in count of the last 0
//We consider a jump to new paragraph when nb of 0 lines > (size of a line) *3
int CountElt(int matrixLen, int Size, int* pProj)
{
    int treshold = MaxBlackPxl(pProj, matrixLen)/2;
    int onSpree = 0;
    int sum = 0;
    int nbVoid = 0;
    int *p = pProj;

    for(int i = 0 ; i < matrixLen ; i++)
    {
        if(onSpree == 0 && *(p+i) > treshold)
        {
            onSpree = 1;
            if(nbVoid >= Size*2)
            {
                sum++;
            }
            nbVoid = 0;
        }
        else if (onSpree == 1 && *(p+i) < treshold)
        {
            sum++;
            nbVoid++;
            onSpree = 0;
        }
        else if (onSpree == 0 && *(p+i) < treshold) 
        {
            nbVoid++;
        }
    }

    return sum;
}


void ijMatrix(int* pProj, struct Matrix lineOrCharMatrix, int matrixLen, int size)
{   
    int treshold = MaxBlackPxl(pProj, matrixLen)/2;
    int onSpree = 0;
    int nbVoid = 0;
    int indexIList = 0;
    int k = 0;

    int *p = pProj;


    for(int i = 0 ; i < matrixLen ; i++)
    {
        if(onSpree == 0 && *(p+i) > treshold)
        {
            onSpree = 1;
            if(nbVoid >= size*2)
            {
                ChangeEltInMatrix(lineOrCharMatrix, indexIList, 0, -1);
                ChangeEltInMatrix(lineOrCharMatrix, indexIList, 1, -1);

                indexIList++;
            }
            nbVoid = 0;

            ChangeEltInMatrix(lineOrCharMatrix, indexIList, 0, i);
        }
        else if (onSpree == 1 && *(p+i) < treshold)
        {
            ChangeEltInMatrix(lineOrCharMatrix, indexIList, 1, i-1);
            onSpree = 0;
            nbVoid++;
            indexIList++;

        }
        else if (onSpree == 0 && *(p+i) < treshold) 
        {
            nbVoid++;
        }
    }
}


void ReconstructText(struct Matrix picture)
{
    //Create ijMatrix according to the picture
    int *pProjH = malloc(sizeof(int)*picture.rows);
    int lineSize = Size(pProjH, picture.rows);
    int lineElt = CountElt(picture.rows, lineSize, pProjH);

    struct Matrix linesMatrix = CreateMatrix(lineElt, 2);
    ijMatrix(pProjH, linesMatrix, picture.rows, lineSize);

    int *linePtr = malloc(sizeof(int)*lineElt);
    int *lineLen = malloc(sizeof(int)*lineElt);

    for(int i = 0 ; i < lineElt+1 ; i++)
    {
        int *pProjV = malloc(sizeof(int)*picture.columns);
        int charSize = Size(pProjV, picture.columns);
        int charElt = CountElt(picture.columns, charSize, pProjV);

        struct Matrix charsMatrix = CreateMatrix(charElt, 2);
        ijMatrix(pProjV, charsMatrix, picture.columns, charSize);

        *(linePtr+i) = &charsMatrix;
        *(lineLen+i) = charElt;
    }

    //TODO: Open file
    //use the previous created matrix to create the file with text in it
    for(int j = 0 ; j < linesMatrix.rows ; j++)
    {
        if (MovePointerInMatrix(linesMatrix, j, 0) == (-1))
        {
            printf("\n    ");
        }
        else
        {
            int im = MovePointerInMatrix(linesMatrix, j, 0);
            int iM = MovePointerInMatrix(linesMatrix, j, 1);
            int *pToJMat = linePtr+j;
            int len = *(lineLen+j); //nb of char in 

            for(int k = 0; k < len ; k++)
            {
                if (*(pToJMat+(k*3)) == (-1))
                {
                    printf(" ");
                }
                else
                {
                    int jm = MovePointerInMatrix(linesMatrix, j, 0);
                    int jM = MovePointerInMatrix(linesMatrix, j, 1);

                    //Recreate matrix and put it into neural net
                    struct Matrix charMat = CreateMatrix(iM-im, jM-jm);
                    //print char
                }
                
            }
            printf("\n");
        }
    }
    //TODO: Close file

}


//Reacreate Matrix -> Prend imin imax, jmin jmax et la picture pour refaire la matrice de l'endroit correspondant
struct Matrix RecreateMatrix(struct Matrix picture, int iMin, int iMax, int jMin, int jMax)
{
    struct Matrix charMat = CreateMatrix(iMax-iMin, jMax-jMin);
}
//


int main()
{
    /*struct Matrix matrix = CreateMatrix(8,4);
    ChangeEltInMatrix(matrix, 1,2,1);
    ChangeEltInMatrix(matrix, 1,1,1);

    ChangeEltInMatrix(matrix, 5,2,1);
    ChangeEltInMatrix(matrix, 5,1,1);

    ChangeEltInMatrix(matrix, 6,2,1);
    ChangeEltInMatrix(matrix, 6,1,1);*/

    struct Matrix matrix = CreateMatrix(2,10);
    ChangeEltInMatrix(matrix, 0,2,1);
    ChangeEltInMatrix(matrix, 0,1,1);
    ChangeEltInMatrix(matrix, 0,8,1);
    ChangeEltInMatrix(matrix, 0,7,1);

    ChangeEltInMatrix(matrix, 1,2,1);
    ChangeEltInMatrix(matrix, 1,1,1);
    ChangeEltInMatrix(matrix, 1,8,1);
    ChangeEltInMatrix(matrix, 1,7,1);

    PrintMatrix(matrix);
    printf("\n");

    int *pProjH = malloc(sizeof(int)*matrix.rows);
    int *pProjV = malloc(sizeof(int)*matrix.columns);


    //TEST VerticalProj
    printf("VerticalProj\n");
    VerticalProjection(matrix, 0, matrix.rows-1, pProjV);
    for(int i = 0 ; i < matrix.columns;i++)
    {
        printf("%i\n", *(pProjV+i));
    }
    printf("\n");


    //TEST HorizontalProj
    printf("HorizontalProj\n");
    HorizontalProjection(matrix, pProjH);
    for(int i = 0 ; i < matrix.rows;i++)
    {
        printf("%i\n", *(pProjH+i));
    }
    printf("\n");


    //TEST CHAR MaxBlackPxl
    printf("CHAR MaxBlackPxl = %i\n", MaxBlackPxl(pProjV, matrix.columns));
    printf("\n");


     //TEST LINE MaxNbOfBlackPxl
    printf("LINE MaxBlackPxl = %i\n", MaxBlackPxl(pProjH, matrix.rows));
    printf("\n");


    //TEST CHAR charSize
    int charSize = Size(pProjV, matrix.columns);
    printf("CHAR CharSize = %i \n", charSize);
    printf("\n");


    //TEST LINE LigneSize
    int lineSize = Size(pProjH, matrix.rows);
    printf("LINE LigneSize = %i\n", lineSize);
    printf("\n");


    //TEST CountCharElt
    int charElt = CountElt(matrix.columns, charSize, pProjV);
    printf("CHAR CoutElt = %i\n", charElt);
    printf("\n");


    //TEST LINE CountLinesElt
    int lineElt = CountElt(matrix.rows, lineSize, pProjH);
    printf("LINE CountElt = %i\n", lineElt);
    printf("\n");


    //TEST iList
    printf("iList\n");
    struct Matrix linesMatrix = CreateMatrix(lineElt,2);
    ijMatrix(pProjH, linesMatrix, matrix.rows, lineSize);
    PrintMatrix(linesMatrix);
    printf("\n");


    //TEST jList
    printf("jList\n");
    struct Matrix charsMatrix = CreateMatrix(charElt,2);
    ijMatrix(pProjV, charsMatrix, matrix.columns, charSize);
    PrintMatrix(charsMatrix);
    printf("\n");

}