# Define the default target.

all: main

# Define dependencies and compile informations

main: main.o base.o 
	gcc main.o base.o -o executable


main.o: main.c base.h
	gcc -c main.c

base.o: base.c
	gcc -c base.c



