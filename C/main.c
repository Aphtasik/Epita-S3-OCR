#include<stdio.h>
#include"Segmentation_Rebuild/trainingSegmentation.h"
#include"Segmentation_Rebuild/Segmentation.h"
#include"Tools/Tools.h"
#include"NeuralNetwork/neural_network.h"
#include "PreProcess/pretraitement.h"
//#include"PreProcess/Rotate.h"

int main()
{
    SDL_Surface *image = load_image("../TestPics/training_01.jpg");
    grayscale(image);
    blackAndWhite(image);
    struct Matrix matrix = SurfaceToMatrix(image);
    double **pAllChar = ReconstructTextTraining(matrix);

    double **input = calloc(sizeof(double*), 68);
    for(int i = 0; i < 68; i++)
    {
        input[i] = calloc(sizeof(double), 900);
        for(int j = 0; j < 900; j++)
        {
            input[i][j] = (double)(rand()%2);
        }
        
    }

    //Network *net = init_nn(900, 150, 68);
    Network *net = load_nn("TrainingData");
    //TRAINING
    double **expected = malloc(sizeof(double*)*68);
    for(int i = 0; i < 68; i++)
    {
        expected[i] = calloc(sizeof(double), 68);
        expected[i][i] = 1.0;
    }

    
    train(net, 1000, 0.3,68, input, expected, "TrainingData", 1);

    for(int i = 0; i < 68; i++)
    {
        free(expected[i]);
    }
    free(expected);


    //TEST reconstruct
    //ReconstructText(matrix, net);
}
