#include<stdio.h>
#include"Segmentation.h"


//AUTHOR: Alexandre GAUTIER


//Makee an histogram with the number of 1 in each line of the binarized matrix
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


//make a matrix of size (x,2) with all list corresponding to the framing of the charactere, wether vertical or horizontal
void ijMatrix(int* pProj, struct Matrix lineOrCharMatrix, int matrixLen, int size)
{   
    int treshold = MaxBlackPxl(pProj, matrixLen)/2;
    int onSpree = 0;
    int nbVoid = 0;
    int indexIList = 0;

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


//Take a struct Matrix and copy the matrix in the indexes into a pointer 
void RecreateMatrix(struct Matrix picture, double *ptr, int iMin, int iMax, int jMin, int jMax)
{
    for(int i = 0 ; i <= iMax-iMin; i++)
    {
        for(int j = 0; j <= jMax-jMin; j++)
        {
            *(ptr+i*30+j) = MovePointerInMatrix(picture, iMin+i, jMin+j);
        }
    }
}


//The big boi that combine everything. It takes a binarized Matrix and create a file with the text in it.
void ReconstructText(struct Matrix picture, Network *net)
{   
    //### Creation of all the Elements

    //Line Segmentation
    int *pProjH = malloc(sizeof(int)*picture.rows);
    HorizontalProjection(picture, pProjH);

    int lineSize = Size(pProjH, picture.rows);
    int lineElt = CountElt(picture.rows, lineSize, pProjH);

    struct Matrix linesMatrix = CreateMatrix(lineElt,2);
    ijMatrix(pProjH, linesMatrix, picture.rows, lineSize);

    //Pointers that will help to iterate and get elements from characters matrixes
    int **linePtr = malloc(sizeof(int)*lineElt);
    int *lineLen = malloc(sizeof(int)*lineElt);

    //Char Segmentation for each line
    for(int i = 0 ; i < lineElt ; i++)
    {
        if(MovePointerInMatrix(linesMatrix, i, 0) != (-1))
        {
            int *pProjV = malloc(sizeof(int)*picture.columns);
            VerticalProjection(picture, MovePointerInMatrix(linesMatrix, i, 0), MovePointerInMatrix(linesMatrix, i, 1), pProjV);

            int charSize = Size(pProjV, picture.columns);
            int charElt = CountElt(picture.columns, charSize, pProjV);

            struct Matrix charMatrixToConvert = CreateMatrix(charElt,2);
            ijMatrix(pProjV, charMatrixToConvert, picture.columns, charSize);

            //We convert flatten the Matrix struct / TODO: Not effecient, need to be fixed
            int *charMatrix = malloc(sizeof(int)*charElt*2);
            for(int j = 0; j < charElt; j++)
            {
                for(int k = 0; k < 2; k++)
                {
                    *(charMatrix+j*2+k) = MovePointerInMatrix(charMatrixToConvert, j, k);
                }
            }

            //attribution of the values in the pointed adresses
            *(linePtr+i) = charMatrix; 
            *(lineLen+i) = charElt;
        }
    }


    //### Reacreate text in a text file
    FILE *fptr;
    fptr = fopen("OCR", "w");
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    fprintf(fptr, "    ");

    for(int k = 0 ; k < lineElt ; k++)
    {   
        if (MovePointerInMatrix(linesMatrix, k, 0) == (-1))
        {
            fprintf(fptr, "\n    ");
        }
        else
        {
            int im = MovePointerInMatrix(linesMatrix, k, 0);
            int iM = MovePointerInMatrix(linesMatrix, k, 1);

            int *charMat = *(linePtr+k);

            int len = *(lineLen+k); //nb of char in the line 

            for(int l = 0; l < len ; l++)
            {
                if (*(charMat+l*2) == (-1))
                {
                    fprintf(fptr, " ");
                }
                else
                {
                    int jm = *(charMat+l*2);
                    int jM = *(charMat+l*2+1);

                    double *ptr = calloc(sizeof(int), 900);
                    RecreateMatrix(picture, ptr, im, iM, jm, jM);
                    char c = predictchar(net, ptr);
                    fprintf(fptr, "%c", c);
                }
            }
            fprintf(fptr, "\n");

            free(charMat);
        }
    }
    fclose(fptr);
}
