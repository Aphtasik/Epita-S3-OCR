#include <stdio.h>
#include <stdlib.h>
#include "neural_network.h"

int main(){
	Network *net = init_nn(10,10,10);
	double input[10] = {0,1,1,0,0,0,1,0,1,1};
	forward(net, input);
	printarray(net);
	free_nn(net);
	return 0;
}

void printarray(Network *net){
	for(int i = 0; i < net->NumHidden; i++){
		printf("%f",net->A1[i]);
	}
	printf("\n");
	for(int i = 0; i < net->NumOutput; i++){
		printf("%f",net->Output[i]);
	}
}
