#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <math.h>


typedef struct Network{
	
	int NumInput;
	int NumHidden;
	int NumOutput;

	//first layer:
	double *Input; //tableau des Input
	double *WeightIH; // tableau des poids Input --> Hidden

	//second layer:
	double *Z1;
	double *A1; // tableau des réponse de la première layer 
	double *WeightHO; //tableau des poids Hidden --> Output
	double *BiasH; //tableau des biais de Hidden
	
	//Output layer:
	double *Z2;
	double *Output; //tableau de la sortie du réseau
	double *BiasO; //tableau de biais de l'Output
	double *Error;
	
} Network;

Network *load_nn(char *filepath);

Network *init_nn(int nbI, int nbH, int nbO);

double random();


void forward(Network *net, double *input);

void train(Network *net, size_t epoch, double eta);

void save_nn(Network *net, char *path);


#endif
