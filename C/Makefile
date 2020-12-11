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

pixel_operations.o: PreProcess/pixel_operations.c PreProcess/pixel_operations.h
	$(CC) -c $< $(CFLAGS) -ISDL2 -ISDL2_image

grayscale.o: PreProcess/grayscale.c PreProcess/pixel_operations.h
	$(CC) -c $< $(CFLAGS) -ISDL2 -ISDL2_image

clean:
	rm -rf *.o

mrpropre: clean
	rm -rf $(EXEC)