#include<stdio.h>
#include"Segmentation_Rebuild/trainingSegmentation.h"
#include"Segmentation_Rebuild/Segmentation.h"
#include"Tools/Tools.h"
#include"NeuralNetwork/neural_network.h"
#include "PreProcess/pixel_operations.h"
#include "PreProcess/pretraitement.h"
//#include"PreProcess/Rotate.h"

int main()
{
    //struct Matrix matrix = SurfaceToMatrix() //TODO: DONNER L'IMAGE
    Network *net = init_nn(900, 150, 68);
    //TEST reconstruct
    //ReconstructText(matrix, net);

    //TRAINING
    double **expected = malloc(sizeof(double*)*68);
    for(int i = 0; i < 68; i++)
    {
        expected[i] = calloc(sizeof(double), 68);
        expected[i][i] = 1.0;
    }

    //double **pAllChar = ReconstructTextTraining(matrix);
    //train(net, 3, 0.3,68, pAllChar, expected, "TrainingData", 1);

    for(int i = 0; i < 68; i++)
    {
        free(expected[i]);
    }
    free(expected);

    printf("fin");
}
