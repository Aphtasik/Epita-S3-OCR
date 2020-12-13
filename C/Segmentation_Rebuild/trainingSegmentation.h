#ifndef TRAININGSEGMENTATION_H
#define TRAININGSEGMENTATION_H

#include<stdio.h>
#include"../Tools/Tools.h"
#include "../NeuralNetwork/testnn/nr2.h"
#include"Segmentation.h"

double ** ReconstructTextTraining(struct Matrix picture);

#endif