#include<stdio.h>
#include"Segmentation_Rebuild/trainingSegmentation.h"
#include"Segmentation_Rebuild/Segmentation.h"
#include"Tools/Tools.h"
#include"NeuralNetwork/neural_network.h"
#include "PreProcess/pretraitement.h"
#include "PreProcess/Rotate.h"

int main()
{
    //OUVERTURE ET TRAITEMENT
    //Load de l'image
    SDL_Surface *image = load_image("../TestPics/image.jpg");

    //Pretraitement (filtre/rotation non utilises sur l'image)
    grayscale(image);
    blackAndWhite(image);
    SDL_Surface *image3 = filtre(image);
    //SDL_Surface *image4 = filtre2(image3);
    if((SDL_SaveBMP(Rotation(image, 20), "image2_rotate.jpg")) != 0){
        exit(EXIT_FAILURE);
    }

    //Passage de SDL à matrice
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
