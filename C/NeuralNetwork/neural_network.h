#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <math.h>


typedef struct Network{
	
	int NumInput;
	int NumHidden;
	int NumOutput;

	//first layer:
	//double *Input; //tableau des inputs
	double *WeightIH; // tableau des poids Input --> Hidden

	//second layer:
	double *A1; // tableau des réponse de la première layer 
	double *WeightHO; //tableau des poids Hidden --> Output
	double *BiasH; //tableau des biais de Hidden
	
	//Output layer:
	double *Output; //tableau de la sortie du réseau
	double *BiasO; //tableau de biais de l'Output
	
} Network;

Network *init_nn(int nbI, int nbH, int nbO);

void forward(Network *net, double *input);

void train(Network *net, size_t epoch, double eta);

void save_nn(Network *net, char *path);


#endif
