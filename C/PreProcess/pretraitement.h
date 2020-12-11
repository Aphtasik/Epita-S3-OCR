#ifndef PRETRAITEMENT_H_
#define PRETRAITEMENT_H_

#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <SDL.h>
#include "pretraitement.h"
#include <math.h>

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void update_surface(SDL_Surface* screen, SDL_Surface* image);
void grayscale(SDL_Surface* surface);
void histo1(SDL_Surface *surface, int L[], int width, int height);
int otsu_threshold(SDL_Surface *surface, int width, int height);
void blackAndWhite(SDL_Surface *surface);
SDL_Surface* filtre(SDL_Surface *surface);

#endif
