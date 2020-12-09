CC=gcc
CFLAGS=-W -Wall -Wextra
LDFLAGS=
EXEC= main

all: $(EXEC)

main: Segmentation_Rebuild/Segmentation.o Segmentation_Rebuild/trainingSegmentation.o NeuralNetwork/neural_network.o Tools/Tools.o main.o
	$(CC) $^ -o $@ -lm

main.o: main.c Segmentation_Rebuild/Segmentation.h NeuralNetwork/neural_network.h Tools/Tools.h
	$(CC) -c $< $(CFLAGS)

Segmentation.o: Segmentation_Rebuild/Segmentation.c Segmentation_Rebuild/Segmentation.h NeuralNetwork/neural_network.h Tools/Tools.h
	$(CC) -c $< $(CFLAGS)

Tools.o: Tools/Tools.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrpropre: clean
	rm -rf $(EXEC)