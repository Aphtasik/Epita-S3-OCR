#include<stdio.h>
#include"Segmentation_Rebuild/trainingSegmentation.h"
#include"Segmentation_Rebuild/Segmentation.h"
#include "Tools/Tools.h"

int main()
{
    struct Matrix matrix = CreateMatrix(10, 17);
    ChangeEltInMatrix(matrix, 2,2,1);
    ChangeEltInMatrix(matrix, 2,3,1);
    ChangeEltInMatrix(matrix, 3,2,1);
    ChangeEltInMatrix(matrix, 4,2,1);
    ChangeEltInMatrix(matrix, 4,3,1);

    ChangeEltInMatrix(matrix, 2,5,1);
    ChangeEltInMatrix(matrix, 2,6,1);
    ChangeEltInMatrix(matrix, 3,5,1);
    ChangeEltInMatrix(matrix, 3,6,1);
    ChangeEltInMatrix(matrix, 4,6,1);

    ChangeEltInMatrix(matrix, 2,9,1);
    ChangeEltInMatrix(matrix, 3,8,1);
    ChangeEltInMatrix(matrix, 3,9,1);
    ChangeEltInMatrix(matrix, 4,8,1);
    ChangeEltInMatrix(matrix, 4,9,1);

    ChangeEltInMatrix(matrix, 2,11,1);
    ChangeEltInMatrix(matrix, 2,12,1);
    ChangeEltInMatrix(matrix, 3,11,1);
    ChangeEltInMatrix(matrix, 3,12,1);
    ChangeEltInMatrix(matrix, 4,11,1);

    /*struct Matrix matrix = CreateMatrix(16, 11);
    ChangeEltInMatrix(matrix, 1,2,1);
    ChangeEltInMatrix(matrix, 1,3,1);
    ChangeEltInMatrix(matrix, 2,2,1);
    ChangeEltInMatrix(matrix, 2,3,1);

    ChangeEltInMatrix(matrix, 1,8,1);
    ChangeEltInMatrix(matrix, 1,9,1);
    ChangeEltInMatrix(matrix, 2,8,1);
    ChangeEltInMatrix(matrix, 2,9,1);

    ChangeEltInMatrix(matrix, 7,1,1);
    ChangeEltInMatrix(matrix, 7,2,1);
    ChangeEltInMatrix(matrix, 8,1,1);
    ChangeEltInMatrix(matrix, 8,2,1);

    ChangeEltInMatrix(matrix, 7,7,1);
    ChangeEltInMatrix(matrix, 7,8,1);
    ChangeEltInMatrix(matrix, 8,7,1);
    ChangeEltInMatrix(matrix, 8,8,1);

    ChangeEltInMatrix(matrix, 12,3,1);
    ChangeEltInMatrix(matrix, 12,4,1);
    ChangeEltInMatrix(matrix, 13,3,1);
    ChangeEltInMatrix(matrix, 13,4,1);

    ChangeEltInMatrix(matrix, 12,7,1);
    ChangeEltInMatrix(matrix, 12,8,1);
    ChangeEltInMatrix(matrix, 13,7,1);
    ChangeEltInMatrix(matrix, 13,8,1);*/

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

    //TEST reconstruct
    ReconstructText(matrix);

    //TRAINING
    FILE *fptr;
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
    fptr = fopen("TrainingData", "w");
    fclose(fptr);
    

}
