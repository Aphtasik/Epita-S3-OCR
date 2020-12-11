CC=gcc
CFLAGS=-W -Wall -Wextra
LDFLAGS=
EXEC= main
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all: $(EXEC)

main: Segmentation_Rebuild/Segmentation.o Segmentation_Rebuild/trainingSegmentation.o NeuralNetwork/neural_network.o Tools/Tools.o main.o
	$(CC) $^ -o $@ -lm

main.o: main.c Segmentation_Rebuild/Segmentation.h NeuralNetwork/neural_network.h Tools/Tools.h PreProcess/Rotate.h PreProcess/grayscale.h
	$(CC) -c $< $(CFLAGS) $(LDLIBS)

Segmentation.o: Segmentation_Rebuild/Segmentation.c Segmentation_Rebuild/Segmentation.h NeuralNetwork/neural_network.h Tools/Tools.h
	$(CC) -c $< $(CFLAGS)

Tools.o: Tools/Tools.c
	$(CC) -c $< $(CFLAGS)

pixel_operations.o: PreProcess/pixel_operations.c PreProcess/pixel_operations.h Tools/Tools.h
	$(CC) -c $< $(CFLAGS) $(LDLIBS)

grayscale.o: PreProcess/grayscale.c PreProcess/pixel_operations.h
	$(CC) -c $< $(CFLAGS) $(LDLIBS)

clean:
	rm -rf *.o

mrpropre: clean
	rm -rf $(EXEC)