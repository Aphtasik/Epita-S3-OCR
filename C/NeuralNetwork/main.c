#include <stdio.h>
#include <stdlib.h>
#include "neural_network.h"
#include "matrix_fn/matrix.h"

void print_nn(Network *net){

    printf("WeightIH: \n");
    for (int i = 0; i < net->NumInput; i++)
    {
        for (int j = 0; j < net->NumHidden; j++)
        {
            printf("%f ", net->WeightIH[i][j]);
        }
        printf("\n");
    }
    printf("\n\nBiasH:\n");

    for (int j = 0; j < net->NumHidden; j++)
    {
        printf("%f ", net->BiasH[j]);
    }
    printf("\n\nWeightHO:\n");
    for (int j = 0; j < net->NumHidden; j++)
    {
        for (int k = 0; k < net->NumOutput; k++)
        {
            printf("%f ", net->WeightHO[j][k]);
        }
        printf("\n");
    }
    printf("\n\nBiasO:\n");
    for (int k = 0; k < net->NumOutput; k++)
    {
        printf("%f ", net->BiasO[k]);
    }
    printf("\n\nZ1 A1:\n");

    for (int i = 0; i < net->NumHidden; i++)
    {
        printf("%f ", net->Z1[i]);
        printf("%f ", net->A1[i]);
    }
    printf("\n\nZ2 Output:\n");
    for (int i = 0; i < net->NumOutput; i++)
    {
        printf("%f ", net->Z2[i]);
        printf("%f ", net->Output[i]);
    }
}

int main(){
    double in[10] = {1,255,3,83,22,2,8,203,66,9};
    double *input = in;
    double expec[2] = {0,1};
    double *expected = expec;
    Network *net = init_nn(10,5,2,10,1);
    print_nn(net);
    forward(net,input);
    print_nn(net);
    train(net,10,0.1,input,expected);
    forward(net,in);
    print_nn(net);
}
