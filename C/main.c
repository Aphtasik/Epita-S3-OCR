#include<stdio.h>
#include"Segmentation_Rebuild/trainingSegmentation.h"
#include"Segmentation_Rebuild/Segmentation.h"
#include"Tools/Tools.h"
#include"NeuralNetwork/testnn/nr2.h"
#include "PreProcess/pretraitement.h"
//#include"PreProcess/Rotate.h"

int main()
{
    /*struct Matrix matrix = CreateMatrix(6, 10);
    ChangeEltInMatrix(matrix, 1, 1, 1);
    ChangeEltInMatrix(matrix, 1, 2, 1);
    ChangeEltInMatrix(matrix, 2, 1, 1);
    ChangeEltInMatrix(matrix, 2, 2, 1);
    ChangeEltInMatrix(matrix, 1, 1, 1);
    ChangeEltInMatrix(matrix, 1, 4, 1);
    ChangeEltInMatrix(matrix, 1, 5, 1);
    ChangeEltInMatrix(matrix, 2, 4, 1);
    ChangeEltInMatrix(matrix, 2, 5, 1);
    ChangeEltInMatrix(matrix, 1, 1, 1);
    ChangeEltInMatrix(matrix, 1, 1, 1);
    ChangeEltInMatrix(matrix, 1, 1, 1);
    ChangeEltInMatrix(matrix, 1, 1, 1);

    PrintMatrix(matrix);
    printf("\n\n");*/

    SDL_Surface *image = load_image("../TestPics/training_01.jpg");
    grayscale(image);
    blackAndWhite(image);
    struct Matrix matrix = SurfaceToMatrix(image);

    //Network *net = initNet(2500, 150, 62);
    Network *net = OpenNr("TrainingData");
    double **pAllChar = ReconstructTextTraining(matrix);

    //TRAINING
    double **expected = malloc(sizeof(double*)*68);
    for(int i = 0; i < 68; i++)
    {
        expected[i] = calloc(sizeof(double), 68);
        expected[i][i] = 1.0;
    }

    //trainNetwork(net, 10, 0.3, 0.9, pAllChar, expected, 62);
    //saveNr(net, "TrainingData");

    for(int i = 0; i < 68; i++)
    {
        free(expected[i]);
    }
    free(expected);


    //TEST reconstruct
    /*Network *net = OpenNr("TrainingData");
    ReconstructText(matrix, net);*/



    //PrintMatrix(matrix);
    /*printf("\n");

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
    ReconstructText(matrix, net);*/
}
