#ifndef TRAININGSEGMENTATION_H
#define TRAININGSEGMENTATION_H

#include<stdio.h>
#include"../Tools/Tools.h"
#include "../NeuralNetwork/neural_network.h"
#include"Segmentation.h"

double ** ReconstructTextTraining(struct Matrix picture);

#endif