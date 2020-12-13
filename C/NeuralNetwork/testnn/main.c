#include <stdio.h>
#include <stdlib.h>
#include "nr2.h"

int main()//int argc, char const *argv[])
{
	Network *net = initNet(900,150,68);
	//Network *net = OpenNr("nn");
	/*
	net->Numpattern = 4;
	double **input  = malloc(sizeof(double *) * net->Numpattern);
	input[0] = malloc(sizeof(double) * 2);
	input[0][0] = 0;
	input[0][1] = 1;
	input[1] = malloc(sizeof(double) * 2);
	input[1][0] = 1;
	input[1][1] = 1;
	input[2] = malloc(sizeof(double) * 2);
	input[2][0] = 1;
	input[2][1] = 0;
	input[3] = malloc(sizeof(double) * 2);
	input[3][0] = 0;
	input[3][1] = 0;
	double **target = malloc(sizeof(double *) * net->Numpattern);
	target[0] = malloc(sizeof(double) * 1);
	target[0][0] = 1;
	target[1] = malloc(sizeof(double) * 1);
	target[1][0] = 0;
	target[2] = malloc(sizeof(double) * 1);
	target[2][0] = 1;
	target[3] = malloc(sizeof(double) * 1);
	target[3][0] = 0;
	*/
	double **input = calloc(sizeof(double*), 68);

	for (int i = 0; i < 68; i++)
	{
		input[i] = calloc(sizeof(double),900);
		for (int j = 0; j < 900; j++)
		{
			input[i][j] = (double) (rand()%2);			
		}
	}
	double **expected = malloc(sizeof(double) * 68);
	for (int i = 0; i < 68; i++)
	{
		expected[i] = calloc(sizeof(double),900);
		expected[i][i] = 1.0;
	}
	
	//trainNetwork(net, 10, 0.1, 0.9, input, expected, 68);
    //printNr(net);

    double **inputest = malloc(sizeof(double*));
    inputest[0] = malloc(sizeof(double) * 2);
    inputest[0][0] = 0;
    inputest[0][1] = 1;

    char x = PredictChar(net,input[0]);
	printf("%c", x);
    freeNetwork(net);

    for (size_t i = 0; i < 68; i++)
    {
        free(input[i]);
        free(expected[i]);
    }
    free(input);
    free(expected);
    free(inputest[0]);
    free(inputest);
    
	return 0;
}