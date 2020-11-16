#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// utiliser sudo apt install libsdl2-dev et compiler avec gcc -o main -lSDL2 main.c et la compilation réussi

int main(){
    if (SDL_Init(SDL_INIT_VIDEO) == -1){
        fprintf(stderr,"erreur de chargement de SDL: %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}
