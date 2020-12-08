#all: Segmentation

#Segmentation: Segmentation.o
#	gcc Segmentation.o Tools.o -o Segmentation

#Segmentation.o: Segmentation.c Tools.h
#	gcc -c Segmentation.c

# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD
CFLAGS = -Wall -Wextra -std=c99 -O0 -g
LDFLAGS =
LDLIBS = -lm

SRC = Segmentation.c Tools.c NeuralNetwork/neural_network.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEP} main

-include ${DEP}

# END