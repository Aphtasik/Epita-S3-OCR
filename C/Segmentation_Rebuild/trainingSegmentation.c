#include<stdio.h>
#include"trainingSegmentation.h"

void ReconstructTextTraining(struct Matrix picture)
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
    double **pAllChar = malloc(sizeof(double*)*68);
    Network *net = init_nn(900, 150, 62, 10, 1);
    
    for(int k = 0 ; k < lineElt ; k++)
    {   
        if (MovePointerInMatrix(linesMatrix, k, 0) != (-1))
        {
            int im = MovePointerInMatrix(linesMatrix, k, 0);
            int iM = MovePointerInMatrix(linesMatrix, k, 1);

            int *charMat = *(linePtr+k);

            int len = *(lineLen+k); //nb of char in the line 

            for(int l = 0; l < len ; l++)
            {
                if (*(charMat+l*2) != (-1))
                {
                    int jm = *(charMat+l*2);
                    int jM = *(charMat+l*2+1);

                    double *ptr = calloc(900, sizeof(int));
                    RecreateMatrix(picture, ptr, im, iM, jm, jM);

                    *(pAllChar+l) = ptr;

                    free(ptr);
                }
            }
            free(charMat);
        }
    }
    free(pProjH);
    free(picture.pmatrix);
    free(lineLen);
    free(linePtr);
    free(linesMatrix.pmatrix);
}