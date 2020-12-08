#include <stdio.h>
#include <stdlib.h>
#include "neural_network.h"

// AUTHOR: Mathis Guilbaud

//simple sigmoid function
double sigmoid(double x){
	return (1.0 / (1.0 + exp(-x)));
}

//derivative of the sigmoid function
double dsigmoid(double x){
	return (sigmoid(x)*(1 - sigmoid(x)));
}

//randomize function to initialize weights and biases
double randomize(){
	return (double)rand()/((double)RAND_MAX);
}


//function used to shuffle input data for a better learning 
void shuffle(double **input, int Inputlength){
	double* tmp;
	int pos = 0;
	for(int i = 0; i < Inputlength - 1; i++){
		pos                = rand() % (Inputlength - i - 1);
		tmp                = input[pos];
		input[pos]         = input[Inputlength - i - 1];
		input[Inputlength - i - 1] = tmp;
	}
}

// free all the network component and the network
void free_nn(Network *net){
	free(net->Input);
	for(int i = 0; i < net->NumInput; i++){
		free(net->WeightIH[i]);
		free(net->GradWeightIH[i]);
	}
	free(net->WeightIH);
	free(net->GradWeightIH);
	
	free(net->BiasH);
	free(net->Z1);
	free(net->A1);
	for(int i = 0; i < net->NumHidden; i++){
		free(net->WeightHO[i]);
		free(net->GradWeightHO[i]);
	}
	free(net->WeightHO);
	free(net->GradWeightHO);

	free(net->BiasO);
	free(net->Z2);
	free(net->Output);
	free(net->Error);
	free(net);
}

// save the neural network component in a text file
void save_nn(Network *net, char* filepath){
	FILE *nr = fopen(filepath, "w+");
	if(nr == NULL){
		printf("save_nn: unable to open file");
	}
	fprintf(nr, "%d\n", net->NumInput);
	fprintf(nr, "%d\n", net->NumHidden);
	fprintf(nr, "%d\n", net->NumOutput);
	fprintf(nr, "%d\n", net->Batch_size);
	fprintf(nr, "%d\n", net->NbTrainingData); //WARNING : modify it according to the nb of training data

	for(int i = 0; i < net->NumInput ; i++){
		for(int j = 0; j < net->NumHidden;j++){
			fprintf(nr,"%lf\n", net->GradWeightIH[i][j]);
			fprintf(nr,"%lf\n", net->WeightIH[i][j]);
		}
	}

	for(int k = 0; k < net->NumOutput ; k++){
		for(int j = 0; j < net->NumHidden;j++){
			fprintf(nr,"%f\n", net->GradWeightHO[j][k]);
			fprintf(nr,"%f\n", net->WeightHO[j][k]);
		}
	}

	for (int j = 0; j < net->NumHidden; j++)
	{
		fprintf(nr, "%f\n", net->BiasH[j]);
	}
	for (int k = 0; k < net->NumOutput; k++)
	{
		fprintf(nr, "%f\n", net->BiasO[k]);
	}

	fclose(nr);
	free_nn(net);
}

//load a neural network from a text file
Network *load_nn(char* filepath){
	Network *net = malloc(sizeof(Network));
	FILE *nr = fopen(filepath, "r");
	if(nr == NULL){
		printf("load_nn: cannot open the file");
		return NULL;
	}
	fscanf(nr, "%d\n", &net->NumInput);
	fscanf(nr, "%d\n", &net->NumHidden);
	fscanf(nr, "%d\n", &net->NumOutput);
	fscanf(nr, "%d\n", &net->Batch_size);
	fscanf(nr, "%d\n", &net->NbTrainingData); //WARNING : modify it according to the nb of training data
	net->GradWeightIH = malloc(sizeof(double *) * net->NumInput);
	net->WeightIH      = malloc(sizeof(double *) * net->NumInput);
	for(int i = 0; i < net->NumInput; i++){
		net->GradWeightIH[i] = malloc(sizeof(double) * net->NumHidden);
		net->WeightIH[i]      = malloc(sizeof(double) * net->NumHidden);
		for(int j = 0; j < net->NumHidden;j++){
			fscanf(nr,"%lf\n", &net->GradWeightIH[i][j]);
			fscanf(nr,"%lf\n", &net->WeightIH[i][j]);
		}
	}

	net->GradWeightHO  = malloc(sizeof(double*) * net->NumHidden);
	net->WeightHO      = malloc(sizeof(double*) * net->NumHidden);
	for(int j = 0; j < net->NumHidden; j++){
		net->GradWeightHO[j] = malloc(sizeof(double) * net->NumOutput);
		net->WeightHO[j]      = malloc(sizeof(double) * net->NumOutput);
	}
	for(int k = 0; k < net->NumOutput; k++){
		for(int j = 0; j < net->NumHidden;j++){
			fscanf(nr,"%lf\n", &net->GradWeightHO[j][k]);
			fscanf(nr,"%lf\n", &net->WeightHO[j][k]);
		}
	}

	net->BiasH = malloc(sizeof(double) * net->NumHidden);
	net->BiasO = malloc(sizeof(double) * net->NumOutput);
	//for (int j = 0; j < net->NumHidden; j++){
		fscanf(nr, "%lf\n", net->BiasH/*[j]*/);
	//}
	//for (int k = 0; k < net->NumOutput; k++)
	//{
		fscanf(nr, "%lf\n", net->BiasO/*[k]*/);
	//}
	fclose(nr);

	net->Input = malloc(sizeof(double) * net->NumInput);
	net->Z1 = calloc(sizeof(double),net->NumHidden);
	net->A1 = calloc(sizeof(double),net->NumHidden);

	net->Z2 = calloc(sizeof(double),net->NumOutput);
	net->Output = calloc(sizeof(double),net->NumOutput);

	net->Error = calloc(sizeof(double), net->Batch_size);

	return net;
}

// initialize a neural network
Network *init_nn(int nbI, int nbH, int nbO, int batch_size, int nbtrainingdata){

	Network *net = malloc(sizeof(Network));
	if(net == NULL)
		return NULL;

	net->NumInput = nbI;	
	net->NumHidden = nbH;
	net->NumOutput = nbO;
	net->Batch_size = batch_size;
	net->NbTrainingData = nbtrainingdata;

	net->Input = malloc(sizeof(double) * net->NumInput);

	net->WeightIH = malloc(sizeof(double*) * net->NumInput);
	net->GradWeightIH = malloc(sizeof(double*) * net->NumInput);
	for(int i = 0; i < net->NumInput; i++){
		net->WeightIH[i] = calloc(sizeof(double), net->NumHidden);
		net->GradWeightIH[i] = calloc(sizeof(double),net->NumHidden);
	}
	for(int i = 0; i < net->NumInput; i++){
		for(int j=0; j < net->NumHidden; j++){
			net->WeightIH[i][j] = randomize();
		}
	}

	net->Z1 = calloc(net->NumHidden, sizeof(double));

	net->A1 = calloc(net->NumHidden, sizeof(double));
	if(net->A1 == NULL)
		return NULL;

	net->BiasH = malloc(sizeof(double) * net->NumHidden);
	if(net->BiasH == NULL)
		return NULL;
	for(int i=0; i < net->NumHidden; i++){
		net->BiasH[i] = randomize();
	}

	net->WeightHO = malloc(sizeof(double*) * net->NumHidden);
	net->GradWeightHO= malloc(sizeof(double*) * net->NumHidden);
	for(int j = 0; j < net->NumHidden; j++){
		net->GradWeightHO[j] = calloc(sizeof(double), net->NumOutput);
		net->WeightHO[j] = calloc(sizeof(double), net->NumOutput);
	}
	for(int j = 0; j < net->NumHidden; j++){
		for(int k=0; k < net->NumOutput; k++){
			net->WeightHO[j][k] = randomize();
		}
	}

	net->BiasO = malloc(sizeof(double) * net->NumOutput);
	if(net->BiasO == NULL)
		return NULL;
	for(int k=0; k < net->NumOutput; k++){
		net->BiasO[k] = randomize();
	}

	net->Z2 = calloc(net->NumOutput, sizeof(double));

	net->Output = calloc(net->NumOutput, sizeof(double));
	if(net->Output == NULL)
		return NULL;

	net->Error = calloc(net->Batch_size, sizeof(double));

	return net;
}

// compute the forward propagation of the neural network
void forward(Network *net ,double *input){
	for (int i = 0; i < net->NumInput; i++)
	{
		net->Input[i] = input[i];
	}
	
	for(int j = 0; j < net->NumHidden; j++){
		for (int i = 0; i < net->NumInput; i++)
		{
			net->Z1[j] += input[i] * net->WeightIH[i][j];
		}
		net->Z1[j] += net->BiasH[j];
	}

	for (int j = 0; j < net->NumHidden; j++)
	{
		net->A1[j] = sigmoid(net->Z1[j]);
	}
		
	for (int k = 0; k < net->NumOutput; k++)
	{
		for (int j = 0; j < net->NumHidden;j++)
		{
			net->Z2[k] += net->A1[j] * net->WeightHO[j][k];		
		}
		net->Z2[k] += net->BiasO[k];
		
	}
	for (int k = 0; k < net->NumOutput; k++)
	{
		net->Output[k] = sigmoid(net->Z2[k]);
	}
		
}

//This function compute the gradients of all weights and put it into the grad arrays of the network
void backpropW(Network *net, double *expected,int batch_index){

	for (int k = 0; k < net->NumOutput; k++)
	{
		net->Error[batch_index] += (net->Output[k] - expected[k]) * (net->Output[k] - expected[k]);
	}

	double *dCawHO = calloc(sizeof(double), net->NumOutput);
	double *dazwHO = calloc(sizeof(double), net->NumOutput);
	double *dzwWHO = calloc(sizeof(double), net->NumHidden);

	double *dCawIH = calloc(sizeof(double), net->NumHidden);
	double *dazwIH = calloc(sizeof(double), net->NumHidden);
	double *dzwWIH = calloc(sizeof(double), net->NumInput);

	for (int k = 0; k < net->NumOutput; k++)
	{
		dCawHO[k] = 2* (net->Output[k] - expected[k]);
		dazwHO[k] = dsigmoid(net->Z2[k]);
	}
	for (int j = 0; j < net->NumHidden; j++)
	{
		dzwWHO[j] = net->A1[j];
	}

	for ( int k = 0; k < net->NumOutput; k++)
	{
		for (int j = 0; j < net->NumOutput; j++)
		{
			net->GradWeightHO[j][k] = dCawHO[k] * dazwHO[k] * dzwWHO[j];
		}		
	}
	
	for (int j = 0; j < net->NumHidden; j++)
	{
		for (int k = 0; k < net->NumOutput; k++)
		{
			dCawIH[j] += net->WeightHO[j][k] * dsigmoid(net->Z2[k]) * 2*(net->Output[k] - expected[k]);
		}
		
		dazwIH[j] = dsigmoid(net->Z1[j]);
	}
	for (int i = 0; i < net->NumInput; i++)
	{
		dzwWIH[i] = net->Input[i];
	}

	for ( int j = 0; j < net->NumHidden; j++)
	{
		for (int i = 0; i < net->NumInput; i++)
		{
			net->GradWeightIH[i][j] = dCawIH[j] * dazwIH[j] * dzwWIH[i];
		}
		
	}
	free(dCawHO);
	free(dazwHO);
	free(dzwWHO);
	free(dCawIH);
	free(dazwIH);
	free(dzwWIH);
}

// This function compute the gradient of all the biases of the network
double* backpropB(Network *net, double *expected){
	double *gradB = calloc(sizeof(double), net->NumHidden + net->NumOutput);

	double *dCawBO = calloc(sizeof(double), net->NumOutput);
	double *dazwBO = calloc(sizeof(double), net->NumOutput);

	double *dCawBH = calloc(sizeof(double), net->NumHidden);
	double *dazwBH = calloc(sizeof(double), net->NumHidden);

	for (int k = 0; k < net->NumOutput; k++)
	{
		dCawBO[k] = 2*(net->Output[k] - expected[k]);
		dazwBO[k] = dsigmoid(net->Z2[k]);
	}
	for (int k = 0; k < net->NumOutput; k++)
	{
		gradB[net->NumHidden - 1 + k] = dCawBH[k] * dazwBH[k];
	}

	for (int j = 0; j < net->NumHidden; j++)
	{
		for (int k = 0; k < net->NumOutput; k++)
		{
			dCawBH[j] += net->BiasO[k] * dsigmoid(net->Z2[k]) * 2 *(net->Output[k] - expected[k]);
		}
		dazwBH[j] = dsigmoid(net->Z1[j]);
	}
	for (int j = 0; j < net->NumHidden; j++)
	{
		gradB[j] = dCawBH[j] * dazwBH[j];
	}

	free(dCawBO);
	free(dCawBH);
	free(dazwBO);
	free(dazwBH);	

	return gradB;	
}

void apply_changes(Network *net, double eta, double *gradB){
	for (int k = 0; k < net->NumOutput; k++){
		for (int j = 0; j < net->NumHidden; j++)
		{
			net->WeightHO[j][k] -= eta * net->GradWeightHO[j][k];
		}
	}
	for (int j = 0; j < net->NumHidden; j++)
	{
		for (int i = 0; i < net->NumInput; i++)
		{
			net->WeightIH[i][j] -= eta * net->GradWeightIH[i][j];
		}
	}

	for (int k = 0; k < net->NumOutput; k++)
	{
		net->BiasO[k] -= eta * gradB[k];
	}
	for (int j = 0; j < net->NumHidden; j++)
	{
		net->BiasH[j] -= eta * gradB[j];
	}
	//reinitializing the arrays
	for (int j = 0; j < net->NumHidden; j++)
	{
		net->Z1[j] = 0;
	}
	for (int k = 0; k < net->NumOutput; k++)
	{
		net->Z2[k] = 0;
	}

	//printf("error: %f ", net->Error[0]);
	net->Error[0] = 0;

}

//function that train the neural network [epoch] times
void train(Network *net, int epoch, double eta, double **input, double **expected){
	for (int x = 0; x < epoch; x++)
	{
		//shuffle(input, net->NbTrainingData);
		for (int y = 0; y < net->NbTrainingData; y++)
		{
			forward(net, input[y]);
			double *gradB = backpropB(net, expected[y]);
			backpropW(net, expected[y], 0);
			apply_changes(net, eta, gradB);
			free(gradB);
		}
	}
	
}

void train1data(Network *net, int epoch, double eta, double *input, double *expected){

	for (int x = 0; x <= epoch; x++)
	{
		forward(net, input);
		double *gradB = backpropB(net, expected);
		backpropW(net, expected, 0);
		apply_changes(net, eta, gradB);
		free(gradB);
	}
	
}

char predictchar(Network *net, double *input){
	char alphabet[62] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	forward(net, input);
	int ires = 0;
	for (int k = 0; k < net->NumOutput; k++)
	{
		if(net->Output[k] >= 0.5){
			ires = k;
		}
	}
	return alphabet[ires];
}