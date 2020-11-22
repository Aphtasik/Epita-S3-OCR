#include <stdio.h>
#include <stdlib.h>
#include "neural_network.h"

int main(){
	Network *net = init_nn(10,10,10);
	double input[10] = {0,1,1,0,0,0,1,0,1,1};
	forward(net, input);
	return 0;
}
