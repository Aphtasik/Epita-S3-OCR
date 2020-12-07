#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <math.h>


typedef struct Network{
	
	int NumInput;
	int NumHidden;
	int NumOutput;
	int Batch_size;
	int NbTrainingData;

	//first layer:
	double *Input; //tableau des Input
	double **WeightIH; // matrice des poids Input --> Hidden
	double **GradWeightIH; // matrice du gradient de WIH

	//second layer:
	double *Z1;
	double *A1; // tableau des réponse de la première layer 
	double **WeightHO; //matrice des poids Hidden --> Output
	double **GradWeightHO; //matrice du gradient de WHO
	double *BiasH; //tableau des biais de Hidden
	
	//Output layer:
	double *Z2;
	double *Output; //tableau de la sortie du réseau
	double *BiasO; //tableau de biais de l'Output
	double *Error; //tableau des erreur de taille nbtrainingdata
	
} Network;
/*
Network *load_nn(char *filepath);
*/
Network *init_nn(int nbI, int nbH, int nbO, int batch_size, int nbtrainingdata);

void free_nn();

double random();


void forward(Network *net, double *input);

char predictchar(Network *net, double *input);

void train(Network *net, int epoch, double eta, double **input, double **expected);

void save_nn(Network *net, char *path);

Network *load_nn(char *filepath);

void train1data(Network *net, int epoch, double eta, double *input, double *expected);

#endif
