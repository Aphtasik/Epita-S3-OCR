#include<stdio.h>
#include"Segmentation_Rebuild/trainingSegmentation.h"
#include"Segmentation_Rebuild/Segmentation.h"
#include"Tools/Tools.h"
#include"NeuralNetwork/neural_network.h"
#include "PreProcess/pretraitement.h"
#include "PreProcess/Rotate.h"
//#include"PreProcess/Rotate.h"

int main()
{
    //OUVERTURE ET TRAITEMENT
    SDL_Surface *image = load_image("../TestPics/image.jpg");
    grayscale(image);
    blackAndWhite(image);
    if((SDL_SaveBMP(Rotation(image, 20), "image2_rotate.jpg")) != 0){
        exit(EXIT_FAILURE);
    }
    struct Matrix matrix = SurfaceToMatrix(image);


    //RECONSTRUCT TEXT
    Network *net = load_nn("TrainingData");
    ReconstructText(matrix, net);


    //ENTRAINEMENT RESEAU
    //Network *net = init_nn(2500, 150, 62);
    //Network *net = load_nn("TrainingData");
    /*double **pAllChar = ReconstructTextTraining(matrix);

    double **expected = malloc(sizeof(double*)*68);
    for(int i = 0; i < 68; i++)
    {
        expected[i] = calloc(sizeof(double), 68);
        expected[i][i] = 1.0;
    }

    //train(net, 10, 0.3, 62, pAllChar, expected, "TrainingData", 1);

    for(int i = 0; i < 68; i++)
    {
        free(expected[i]);
    }
    free(expected);*/
}
