#ifndef ROTATE_H_
#define ROTATE_H_

#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <SDL.h>
#include "pretraitement.h"
#include <math.h>

SDL_Surface* Rotation(SDL_Surface* origine, float angle);
void HorizontalProjection2(SDL_Surface* image, int* pList);
float Moyenne(SDL_Surface* image, int* pList);
float Variance(SDL_Surface* image, int* pList);
int CalculAngle (SDL_Surface* image);
SDL_Surface* VraiRotation(SDL_Surface* image);


#endif
