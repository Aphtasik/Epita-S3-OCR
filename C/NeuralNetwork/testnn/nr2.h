# ifndef NR2_H_
# define NR2_H_

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Network Network;
struct Network{
	float Error;
	int Numpattern;
	int NumHidden;
	int NumInput;
	int NumOutput;
	int is7;

	double *ranpat;
	double *deltaO;
	double *deltaH;
	double *SumDow;

	double **deltaWeightLH;
	double **deltaWeightHO;
	double **WeightLH;
	double **WeightHO;
	double **SumO;
	double **SumH;
	double **Hidden;
	double **Output;

};

//################################Functions###############################

Network *initNet(size_t nbi, size_t nbh, size_t nbo);

char PredictChar(Network *net, double **input);

void trainNetFinal(Network *net);

void trainNetwork(Network *net, size_t _epoch, double eta,\
	double alpha, double **input, double **target);

Network *OpenNr(char *filePath);

void saveNr(Network *net, char *filePath);

void freeNetwork(Network *net); //called in SaveNr

//char *get_string(MatBinTree *mbt, Network *net);

void printNr(Network *net);

# endif