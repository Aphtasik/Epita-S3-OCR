#include <err.h>
#include<stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <SDL.h>
#include "pixel_operations.h"
#include <math.h>
#include "Rotate.h"


SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}


//I retrieve the number of black pixels on each line
void HorizontalProjection(SDL_Surface* image, int* pList)
{
    int sum;
    Uint32 pixel;
    int rows = image->h;
    int columns = image->w;
    int *p = pList;
      
    for(int i = 0; i < rows; i++)
    {
        sum = 0;
        for(int j = 0; j < columns; j++)
        {
	  //I retrieve the pixel in order to look at its colour
	    pixel = get_pixel(image, i, j);
	    Uint8 r,g,b;
	    SDL_GetRGB(pixel,image->format,&r,&g,&b);
            if(r == 0 && g == 0 && b == 0)
            {
                sum+=1;
            }
        }
        *(p+i) = sum;
    }
}


//I calculate the average of my painting containing the number of my black pixels per line

float Moyenne(SDL_Surface* image, int* pList)
{
  float s = 0;
  int rows = image->h;
  int *p = pList;
  for (int i = 0; i < rows; i++)
    {
      s = s + *(p+i);
    }
  return (s/rows); 
}

//I calculate the variance of my table containing the number of my black pixels per line
float Variance(SDL_Surface* image, int* pList)
{
  int *p = pList;
  int rows = image->h;
  float v = 0;
  float m = Moyenne(image,p);
  for (int i = 0; i < rows; i++)
    {
      v = v + (*(p+i) -  m)*(*(p+i) -  m);
    }
  return (v/rows);
}


SDL_Surface* Rotation(SDL_Surface* origine, float angle)
{
  SDL_Surface* destination;
  Uint32 pixel;
  int mx, my, mxdest, mydest;
  int X1, Y1;
  float angle_radian;
  float tcos;
  float tsin;
  double largeurdest;
  double hauteurdest;
 
/*determines the value in radian of the angle*/
  angle_radian = -angle * M_PI / 180.0;
 
/*to avoid a lot of calls, the values are stored*/
  tcos = cos(angle_radian);
  tsin = sin(angle_radian);
 
/*calculating the size of the destination image*/
  largeurdest=   ceil(origine->w * fabs(tcos) + origine->h * fabs(tsin));
  hauteurdest=   ceil(origine->w * fabs(tsin) + origine->h * fabs(tcos));
 
 
/* 
 * allocates the memory to the destination space, attention, 
 * the surface is the same size
 */
  destination = SDL_CreateRGBSurface(SDL_HWSURFACE, largeurdest, hauteurdest, origine->format->BitsPerPixel,
			origine->format->Rmask, origine->format->Gmask, origine->format->Bmask, origine->format->Amask);
 
 /*we check that the memory has been allocated*/
  if(destination==NULL)
    return NULL;
 
 /*calculation of the centre of the images*/
  mxdest = destination->w/2.;
  mydest = destination->h/2.;
  mx = origine->w/2.;
  my = origine->h/2.;

  for(int j=0;j<destination->h;j++)
    for(int i=0;i<destination->w;i++)
     {
        pixel = get_pixel(destination, i, j);
	Uint8 r,g,b;
	SDL_GetRGB(pixel,destination->format,&r,&g,&b);
	pixel = SDL_MapRGB(destination->format, 255, 255,255);
	
	put_pixel(destination, i, j, pixel);
     }
 
  for(int j=0;j<destination->h;j++)
    for(int i=0;i<destination->w;i++)
     {
/* the pixel value that best fits the position is determined.
 * i,j of the destination area */
 
/* the best position on the original surface is determined by applying
 * a reverse rotation matrix
 */
 
       X1 = (ceil (tcos * (i-mxdest) + tsin * (j-mydest) + mx));
       Y1 = (ceil (-tsin * (i-mxdest) + tcos * (j-mydest) + my));
   /* we check that we don't come out of the edges*/
       if (X1>=0 && X1< origine->w && Y1>=0 && Y1< origine->h)
	 {
	   pixel = get_pixel(origine, X1, Y1);
	   put_pixel(destination, i, j, pixel);
	 }
     }
 
  return destination;
}

//I'm looking for my angle of rotation
int CalculAngle (SDL_Surface* image)
{
  int rows = image->h;
  int *p = malloc(sizeof(int)*rows);
  HorizontalProjection(image,p);
  float Var = Variance(image,p);
  float PrecVar = 0;
  int angle = 0;
  //I am looking for my variance when it is at its maximum.
  while (Var > PrecVar)
    {
      PrecVar = Var;
      image = Rotation(image,-1);
      int rows = image->h;
      int *p = malloc(sizeof(int)*rows);
      angle -= 1;
      HorizontalProjection(image,p);
      Var = Variance(image,p);
    }
  return angle;
}

//The function that calls my rotation with its angle
SDL_Surface* VraiRotation(SDL_Surface* image)
{
  int angle = CalculAngle(image);
  image = Rotation(image,angle);
  return image;
}


/*int main()
{
  SDL_Surface* image;

  image = load_image("image2.png");

  //int tableau[3];
  //tableau[0] = 1;
  //tableau[1] = 2;
  //tableau[2] = 3;
  //float res = Variance2(tableau,3);
  //printf("%f\n",res);
  

  //int rows = image->h;
  //int *p = malloc(sizeof(int)*rows);
  //HorizontalProjection(image, p);
  //int maxi = Max(image,p);
  //printf("%i\n",maxi);
  
  //for (int i = 0; i<rows;i++)
  // {
  //   printf("%i\n", *(p+i));
  // }

  //if((SDL_SaveBMP(Rotation(image,-50), "image2_rotate.png")) != 0)
  //  exit(EXIT_FAILURE);

  //if((SDL_SaveBMP(VraiRotation(image), "image2_rotate2.png")) != 0)
  // exit(EXIT_FAILURE); 
  }*/
