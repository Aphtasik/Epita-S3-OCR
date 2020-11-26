#include <stdio.h>
#include <stdlib.h>
#include "neural_network.h"


double sigmoid(double x){
	return (1.0 / (1.0 + exp(-x)));
}

double dsigmoid(double x){
	return (sigmoid(x)*(1 - sigmoid(x)));
}

void free_nn(Network *net){
	free(net->Input);
	free(net->WeightIH);
	free(net->BiasH);
	free(net->Z1);
	free(net->A1);
	free(net->WeightHO);
	free(net->BiasO);
	free(net->Z2);
	free(net->Output);
	free(net);
}


Network *load_nn(char *filepath){
	Network *net = malloc(sizeof(Network));
	FILE *nr = fopen(filpath, "r");
	if(nr == NULL){
		printf("load_nn: cannot open the file");
		return NULL;
	}
	fscanf(nr, "%i\n", &net->NumInput);
	fscanf(nr, "%i\n", &net->NumHidden);
	fscanf(nr, "%i\n", &net->NumOutput);
	net->WeightIH = malloc(sizeof(double) * net->NumInput);
	for(int i = 0; i < net->NumInput; i++){
		fscanf(nr, "%f", &net->WeightIH[i]);
	}

	net->Z1 = malloc(sizeof(double) * net->NumHidden);
	net->A1 = malloc(sizeof(double) * net->NumHidden);
	net->BiasH = malloc(sizeof(double) * net->NumHidden);
	net->WeightHO = malloc(sizeof(double) * net->NumHidden);
	for(int i = 0; i < net->NumHidden; i++){
		fscanf(nr, "%f\n", net->Z1[i]);
		fscanf(nr, "%f\n", net->A1[i]);
		fscanf(nr, "%f\n", net->BiasH[i]);
		fscanf(nr, "%f\n", net->WeightHO[i]
	}
	net->BiasO = malloc(sizeof(double) * net->NumOutput);
	net->Z2 = malloc(sizeof(double) * net->NumOutput);
	net->Output = malloc(sizeof(double) * net->NumOutput);
	for(int i = 0; i < net->NumOutput; i++){
		fscanf(nr, "%f\n", net->BiasO[i]);
		fscanf(nr, "%f\n", net->Z2[i]);
		fscanf(nr, "%f\n", net->Output[i]);
	}
	fclose(nr);
}

void save_nn(Network *net, char *filepath){
	FILE *nr = fopen(filepath, "w+");
	if(nr == NULL){
		printf("save_nn: cannot open the file");
		return NULL;
	}
	fprintf(nr, "%i\n", net->NumInput);
	fprintf(nr, "%i\n", net->NumHidden);
	fprintf(nr, "%i\n", net->NumOutput);

	for(int i = 0; i < net->NumInput, i++){
		fprintf(nr, "%lf\n", net->WeightIH[i]);
	}
	for(int i = 0; i < net->NumHidden; i++){
		fprintf(nr, "%lf\n", net->Z1[i]);
		fprintf(nr, "%f\n", net->A1[i]);
		fprintf(nr, "%f\n", net->BiasH[i]);
		fprintf(nr, "%f\n", net->WeightHO[i]);
	}
	for(int i = 0; i < net->NumOutput; i++){
		fprintf(nr, "%f\n", net->BiasO[i]);
		fprintf(nr, "%f\n", net->Z2[i]);
		fprintf(nr, "%f\n", net->Output[i]);
	}
	fclose(nr);
	free_nn(net);
}

double random(){
	return (double)rand()/((double)RAND_MAX+1);
}

Network *init_nn(int nbI, int nbH, int nbO, int batch_size){

	Network *net = malloc(sizeof(Network));
	if(net == NULL)
		return NULL;

	net->NumInput = nbI;	
	net->NumHidden = nbH;
	net->NumOutput = nbO;
	net->Batch_size = batch_size;

	net->Input = malloc(sizeof(double) * net->NumInput);

	net->WeightIH = malloc(sizeof(double)*net->NumInput);
	if(net->WeightIH == NULL)
		return NULL;

	for(int i = 0; i < net->NumInput;i++){
		net->WeightIH[i] = rand();
	}
	
	net->Z1 = calloc(net->NumHidden, sizeof(double));

	net->A1 = calloc(net->NumHidden, sizeof(double));
	if(net->A1 == NULL)
		return NULL;

	net->BiasH = malloc(sizeof(double) * net->NumHidden);
	if(net->BiasH == NULL)
		return NULL;
	for(int i=0; i < net->NumHidden; i++){
		net->BiasH[i] = rand();
	}

	net->WeightHO = malloc(sizeof(double) * net->NumHidden);
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

	net->Z2 = calloc(net->NumOutput, sizeof(double));

	net->Output = calloc(net->NumOutput, sizeof(double));
	if(net->Output == NULL)
		return NULL;

	net->Error = calloc(net->Batch_size, sizeof(double));

	return net;
}

void forward(Network *net, double *Input){
	for(int i = 0; i < net->NumInput; i++){
		net->Input[i] = Input[i];
	}
	//compute A1:
	for(int i = 0; i < net->NumHidden; i++){
		for(int j = 0; j < net->NumInput; j++){
			net->Z1[i] += net->WeightIH[j] * Input[j]; 
		}
		net->Z1[i] += net->BiasH[i];
		net->A1[i] = sigmoid(net->Z1[i]);
	}

	//compute Output:
	for(int i = 0; i < net->NumOutput; i++){
		for(int j = 0; j < net->NumHidden; j++){
			net->Z2[i] += net->WeightHO[j] * net->A1[j];
		}
		net->Z2[i] += net->BiasO[i];
		net->Output[i] = sigmoid(net->Output[i]);
	}
	//result is stocked in net->Output
}

double *backpropW(Network *net, double *expected, int batch_index){
	double *grad = malloc(sizeof(double) * (net->NumInput + net->NumHidden));

	//array for the derivative operations for the weights
	//hidden layer
	double *dCaWH = malloc(sizeof(double) * net->NumHidden);	
	double *dazWH = malloc(sizeof(double) * net->NumHidden);
	double *dzwWH = malloc(sizeof(double) * net->NumHidden);
	//input layer
	double *dCaWI = malloc(sizeof(double) * net->NumInput);
	double *dazWI = malloc(sizeof(double) * net->NumInput);
	double *dzwWI = malloc(sizeof(double) * net->NumInput);
	
	//array for the derivative operations for the biases
	//output layer
	double *dCaBO = malloc(sizeof(double) * net->NumOutput);
	double *dazBO = malloc(sizeof(double) * net->NumOutput);
	double *dzbBO = malloc(sizeof(double) * net->NumOutput);
	//hidden layer
	double *dCaBH = malloc(sizeof(double) * net->NumHidden);
	double *dazBH = malloc(sizeof(double) * net->NumHidden);

	//computation of the cost function
	for(int i = 0, i < net->NumOutput; i++){
		net->Error[batch_index] += (net->Output[i] - expected[i]) * (net->Output[i] - expected[i]);
	}
	
	//computation of derivative for WeightHO
	for(int i = 0; i < net->NumHidden; i++){
		dCaWH[i] = 2*(net->A1[i] - expected[i]);
		dazWH[i] = dsigmoid(net->Z2[i]);
		dzwWH[i] = net->A1[i];
	}
	//computation of derivative for WeightIH
	for(int i = 0; i < net->NumInput; i++){
		dCaWI[i] = 2*(net->Input[i] - expected[i]);
		dazWI[i] = dsigmoid(net->Z1[i]);
		dzwWI[i] = net->Input[i];
	}

	//gradient computation
	for(int i = 0; i < net->NumInput; i++){
		grad[i] = dCaWI[i] * dazWI[i] * dzwWI[i];
	}
	for(int i = 0; i < net->NumHidden; i++){
		grad[i + net->NumInput -1] = dCaWH[i] * dazWH[i] * dzwWI[i];
	}

	free(dCaWI);
	free(dCaWH);
	free(dazWH);
	free(dazWI);
	free(dzwWH);
	free(dzwWI);
	
	return grad
}

double *backpropB(Network *net, double *expected){
	double *grad = malloc(sizeof(double) * (net->NumOutput + net->NumHidden));

	//allocation derivative arrays
	//Output layer
	double *dCaBO = malloc(sizeof(double) * net->NumOutput);
	double *dazBO = malloc(sizeof(double) * net->NumOutput);

	//Hidden layer
	double *dCaBH = malloc(sizeof(double) * net->NumHidden);
	double *dazBH = malloc(sizeof(double) * net->NumHidden);

	//computation of derivative values
	for(int i = 0; i < net->NumOutput; i++){
		dazBO[i] = dsigmoid(net->Z2[i]);
		dCaBO[i] = 2*(net->Output[i] - expected[i]);
	}

	for(int i = 0; i < net->NumHidden; i++){
		dazBH[i] = dsigmoid(net->Z1[i]);
		dCaBH[i] = 2*(net->A1[i] - expected[i]);
	}

	//gradient computation
	for(int i = 0; i < net->NumOutput; i++){
		grad[i + net->NumHidden -1] = dazBO[i] * dCaBO[i];
	}
	for(int i = 0; i < net->NumHidden; i++){
		grad[i] = dCaBH[i] * dazBH[i];
	}

	free(dCaBO);
	free(dCaBh);
	free(dazBO);
	free(dazBH);

}

void apply_changes(Network *net, double *gradW, double *gradB, double eta){
	//apply changes for weights
	for(int i = 0; i < net->NumInput + net->NumHidden -1; i++){
		if(i < net->NumInput){
			net->WeightIH[i] -= eta * gradW[i];
		}
		else{
			net->WeightHO[i - net->NumInput] -= eta * gradW[i];
		}
	}
	//apply changes for bias
	for(int i = 0; i < net->NumHidden + net-<NumOutput - 1; i++){
		if(i < net->NumHidden){
			net->BiasH[i] -= eta * gradB[i];
		}
		else{
			net->BiasO[i - net->NumHidden] -= eta * gradB[i];
		}
	}
}

void train(Network *net, size_t epoch, double eta, double *input, double *expected){
	double eta = 0.3;
	for(int i = 0; i < epoch; i++){
		forward(net, input);	
		double *gradW = backpropW(net, expected, 0);
		double *gradB = backpropB(net, expected);
		apply_changes(net, gradW, gradB, eta);
	}
}








