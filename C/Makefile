CC=gcc
CFLAGS=-W -Wall -Wextra -std=c99 -O3 `pkg-config --cflags sdl` -MMD
LDFLAGS=
EXEC= main
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm

all: $(EXEC)

main: Segmentation_Rebuild/Segmentation.o Segmentation_Rebuild/trainingSegmentation.o NeuralNetwork/neural_network.o Tools/Tools.o PreProcess/pretraitement.o main.o PreProcess/Rotate.o
	$(CC) $^ -o $@ $(LDLIBS)

main.o: main.c Segmentation_Rebuild/Segmentation.h NeuralNetwork/neural_network.h Tools/Tools.h PreProcess/pretraitement.h PreProcess/Rotate.h
	$(CC) -c $< $(CFLAGS) 

Segmentation.o: Segmentation_Rebuild/Segmentation.c Segmentation_Rebuild/Segmentation.h NeuralNetwork/neural_network.h Tools/Tools.h
	$(CC) -c $< $(CFLAGS)

trainingSegmentation.o: Segmentation_Rebuild/trainingSegmentation.c Segmentation_Rebuild/trainingSegmentation.h Segmentation_Rebuild/Segmentation.c Segmentation_Rebuild/Segmentation.h NeuralNetwork/neural_network.h Tools/Tools.h
	$(CC) -c $< $(CFLAGS)
	
Tools.o: Tools/Tools.c
	$(CC) -c $< $(CFLAGS)

pretraitement.o: PreProcess/pretraitement.c PreProcess/pixel_operations.h
	$(CC) -c $< $(CFLAGS)

Rotate.o: PreProcess/Rotate.c PreProcess/pretraitement.h
	$(CC) -c $< $(CFLAGS)

neural_network.o: NeuralNetwork/neural_network.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf **/*.o
	rm -rf *.d
	rm -rf **/*.d

mrpropre: clean
	rm -rf $(EXEC)
	rm OCR
	rm image2_rotate.jpg