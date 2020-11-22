#include <stdio.h>
#include <stdlib.h>
#include "neural_network.h"


double sigmoid(double x){
	return (1.0 / (1.0 + exp(-x)));
}

double dsigmoid(double x){
	return (sigmoid(x)*(1 - sigmoid(x)));
}

/*
Network *load_nn(char *path){

}
*/

double random(){
	return (double)rand()/((double)RAND_MAX+1);
}

Network *init_nn(int nbI, int nbH, int nbO){

	Network *net = malloc(sizeof(Network));
	net->NumInput = nbI;
	net->NumHidden = nbH;
	net->NumOutput = nbO;

	//net->Input = malloc(sizeof(double) * NumInput);
	net->WeightIH = malloc(sizeof(double) * net->NumInput);
	for(int i = 0; i < net->NumInput;i++){
		net->WeightIH[i] = rand();
	}

	net->A1 = malloc(sizeof(double) * net->NumHidden);
	net->BiasH = malloc(sizeof(double) * net->NumHidden);
	for(int i=0; i < net->NumHidden; i++){
		net->BiasH[i] = rand();
	}
	net->WeightHO = malloc(sizeof(double)* net->NumHidden);
	for(int i = 0; i < net->NumHidden; i++){
		net->WeightHO[i] = rand();
	}

	net->BiasO = malloc(sizeof(double) * net->NumOutput);
	for(int i=0; i < net->NumOutput; i++){
		net->BiasO[i] = rand();
	}
	net->Output = malloc(sizeof(double)* net->NumOutput);

	return net;
}

void forward(Network *net, double *Input){
	//compute A1:
	for(int i = 0; i < net->NumHidden; i++){
		for(int j = 0; j < net->NumInput; j++){
			net->A1[i] += net->WeightIH[j] * Input[j]; 
		}
		net->A1[i] += net->BiasH[i];
		net->A1[i] = sigmoid(net->A1[i]);
	}

	//compute Output:
	for(int i = 0; i < net->NumOutput; i++){
		for(int j = 0; j < net->NumHidden; j++){
			net->Output[i] += net->WeightHO[j] * net->A1[j];
		}
		net->Output[i] += net->BiasO[i];
		net->Output[i] = sigmoid(net->Output[i]);
	}
	//result is stocked in net->Output
}

void train(Network *net, size_t epoch, double eta){

}

void save_nn(Network *net, char *path){

}
