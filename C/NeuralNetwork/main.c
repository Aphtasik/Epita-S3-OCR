#include <stdio.h>
#include <stdlib.h>
#include "neural_network.h"

void printarray(Network *net, double *input){
	for(int i = 0; i < net->NumInput; i++){
		printf(" %f ",input[i]);
	}
	printf("\n\n");
	for(int i = 0; i < net->NumInput; i++){
		printf(" %f ",net->WeightIH[i]);
	}
	printf("\n\n");
	for(int i = 0; i < net->NumHidden; i++){
		printf(" %f ", net->BiasH[i]);
	}
	printf("\n\n");
	for(int i = 0; i < net->NumHidden; i++){
		printf(" %f ",net->A1[i]);
	}
	printf("\n\n");
	for(int i = 0; i < net->NumOutput; i++){
		printf(" %f ",net->Output[i]);
	}
	printf("\n\n");
}

int main(){
	char *filepath = "";
	Network *net = load_nn(filepath);
	if(net == NULL){
		Network *net = init_nn(10,10,10);
	}
	double *input = malloc(sizeof(double) * net->NumInput);
	for(int i = 0; i < net->NumInput; i++){
		input[i] = i%3;
	}
	forward(net, input);
	printarray(net, input);
	free_nn(net);
	free(input);
	return 0;
}


