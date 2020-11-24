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
	//printf("%zu\n",sizeof(Network));

	Network *net = malloc(sizeof(Network));
	if(net == NULL)
		return NULL;

	net->NumInput = nbI;
	//printf("%i\n",net->NumInput);
	
	net->NumHidden = nbH;
	net->NumOutput = nbO;

	net->NumInput = malloc(sizeof(double) * net->NumInput);
	if(net->NumInput == NULL)
		return NULL;

	net->WeightIH = malloc(sizeof(double)*net->NumInput);
	if(net->WeightIH == NULL)
		return NULL;

	for(int i = 0; i < net->NumInput;i++){
		net->WeightIH[i] = rand();
	}

	net->A1 = malloc(sizeof(double) * net->NumHidden);
	if(net->A1 == NULL)
		return NULL;

	net->BiasH = malloc(sizeof(double) * net->NumHidden);
	if(net->BiasH == NULL)
		return NULL;
	for(int i=0; i < net->NumHidden; i++){
		net->BiasH[i] = rand();
	}

	net->WeightHO = malloc(sizeof(double)* net->NumHidden);
	if(net->WeightHO == NULL)
		return NULL;
	for(int i = 0; i < net->NumHidden; i++){
		net->WeightHO[i] = rand();
	}

	net->BiasO = malloc(sizeof(double) * net->NumOutput);
	if(net->BiasO == NULL)
		return NULL;
	for(int i=0; i < net->NumOutput; i++){
		net->BiasO[i] = rand();
	}

	net->Output = malloc(sizeof(double)* net->NumOutput);
	if(net->Output == NULL)
		return NULL;

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

void free_nn(Network *net){
	free(net->WeightIH);
	free(net->BiasH);
	free(net->A1);
	free(net->WeightHO);
	free(net->BiasO);
	free(net->Output);
	free(net);
}

void save_nn(Network *net, char *path){

}
