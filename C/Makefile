#NE PAS UTILISER -> PAS FINI

all: main

main: Segmentation_Rebuild/Segmentation.o Segmentation_Rebuild/trainingSegmentation.o NeuralNetwork/neural_network.o Tools/Tools.o main.o
	gcc Segmentation_Rebuild/Segmentation.o Segmentation_Rebuild/trainingSegmentation.o NeuralNetwork/neural_network.o Tools/Tools.o main.o -o main -lm

main.o: main.c
	gcc -c main.c

Segmentation_Rebuild/Segmentation.o: Segmentation_Rebuild/Segmentation.c 
	gcc -c Segmentation_Rebuild/Segmentation.c