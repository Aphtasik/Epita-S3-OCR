#include <stdio.h>
#include <stdlib.h>
#include "neural_network.h"

void print_nn(Network *net){

    printf("\n\nWeightIH: \n");
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
    printf("\n");
}

int main(){

   // fonction xor 
  /* 
    double in1[2] = {1,0};
    double *in11 = in1;
    double in2[2] = {0,1};
    double *in22 = in2;
    double in3[2] = {1,1};
    double *in33 = in3;
    double in4[2] = {0,0};
    double *in44 = in4;
    double **input = malloc(sizeof(double*) * 4);
    input[0] = in11;
    input[1] = in22;
    input[2] = in33;
    input[3] = in44;
    
    double ex1[1] = {1};
    double *ex11 = ex1;
    double ex2[1] = {1};
    double *ex22 = ex2;
    double ex3[1] = {0};
    double *ex33 = ex3;
    double ex4[1] = {0};
    double *ex44 = ex4;
    double **expected = malloc(sizeof(double*) * 4);
    expected[0] = ex11;
    expected[1] = ex22;
    expected[2] = ex33;
    expected[3] = ex44;
   */ 
   /*  
    double In[2] = {1,1};
    double In2[2] = {0,1};
    double *input2 = In2;
    double *input = In;
    double expected[1] = {0};
    double expected2[1] = {1};
    */
   /*
    Network *net = init_nn(2,2,1,10,4);
    //Network *net = load_nn("nn");
    print_nn(net);
    //forward(net,input);
    forward(net, input[3]);
    train(net, 100000, 0.5, input, expected);
    //train1data(net,1000,0.1,input2,expected2);
    //forward(net,input);
    forward(net, input[2]);
    print_nn(net);
    //forward(net, input2);
    forward(net, input[0]);
    print_nn(net);
    //free_nn(net);
    save_nn(net, "nn");
    free(input);
    free(expected);
    */
    //fin fonction xor

    //character recognition
    /*
    int nbtrainingdata;
    double **chartraining;
    double **charexpected;
    double *charexample;
    Network *net = init_nn(256, 150, 58, 1, nbtrainingdata);
    load_nn("nn");
    train(net, 100000, 0.2, chartrainingdata, charexpected);
    predictchar(net, charexample);
    */

    //Training sur caractères:

    Network *net = init_nn(900,150,68);
    
    double **input = calloc(sizeof(double*), 68);
    
    for (int i = 0; i < 68; i++)
    {
        input[i] = calloc(sizeof(double), 900);
        /*
        for (int j = 0; j < 900 ; i++)
        {
            input[i][j] = (double)(rand() % 2);
        }
        */
    }
    
    double **expected = malloc(sizeof(double*) * 68);
    for(int i = 0; i < 68; i++){
        expected[i] = calloc(sizeof(double), 68);
        expected[i][i] = 1.0;
    }
    
    train(net, 2, 0.3, 68, input, expected, "nn");

    for(int i = 0; i < 68; i++){
        free(expected[i]);
        free(input[i]);
    }
    free(input);
    free(expected);

}
