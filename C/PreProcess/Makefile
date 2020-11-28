all: Segmentation

Segmentation: Segmentation.o
	gcc Segmentation.o ../Tools.o -o Segmentation

Segmentation.o: Segmentation.c ../Tools.h
	gcc -c Segmentation.c

