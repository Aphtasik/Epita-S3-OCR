#include <err.h>
#include <math.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
//#include <SDL.h>
#include "../Tools/Tools.h"

Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch(surface->format->BytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}


void update_surface(SDL_Surface* screen, SDL_Surface* image)
{
    if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    SDL_UpdateRect(screen, 0, 0, image->w, image->h);
}

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}


struct Matrix SurfaceToMatrix(SDL_Surface *image)
{
	int height = image->h;
	int width = image->w;

    struct Matrix matrix = CreateMatrix(height, width);

    for(int i = 0; i < width ; i++)
    {
        for(int j = 0 ; j < height ; j++)
        {
            Uint32 pixel = get_pixel(image, i, j);
            Uint8 r,g,b;
            SDL_GetRGB(pixel, image->format, &r,&g,&b);

            if(g == 0)
            {
                ChangeEltInMatrix(matrix, j, i, 1);
            }
        }
    }
    return matrix;
}


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

SDL_Surface* display_image(SDL_Surface *img)
{
    SDL_Surface *screen;

    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
                img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // return the screen for further uses
    return screen;
}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

void SDL_FreeSurface(SDL_Surface *surface);

SDL_Surface* image_surface;
SDL_Surface* screen_surface;

//fonction permettant le passage d'une image en nuance de gris

void grayscale(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;
    
    for(int i = 0; i < width; i++)
      {
	for(int j = 0; j < height; j++)
	  {
	    Uint32 pixel = get_pixel(image, i, j);

	    Uint8 r, g, b;
	    SDL_GetRGB(pixel, image->format, &r, &g, &b);

	    int average = 0.3*r + 0.59*g + 0.11*b;
 
	    pixel = SDL_MapRGB(image->format, average, average, average);

	    put_pixel(image, i, j, pixel);
	  }
      }
}

//fonction créant un histogramme

void histo1(SDL_Surface *image, int L[], int width, int height)
{
    for(int i = 0; i < width; i++)
      {
	for(int j = 0; j < height; j++)
	  {
	    Uint32 pixel = get_pixel(image, i, j);

	    Uint8 r, g, b;
	    SDL_GetRGB(pixel, image->format, &r, &g, &b);

	    L[r] += 1;
	  }
      }
}

//fonction calculant un seuil grâce à la méthode Otsu

int otsu_threshold(SDL_Surface *image, int width, int height)
{
    int histo[256];

    for (int i = 0; i < 256; i++)
      {
	histo[i] = 0;
      }
    //Initialisation and creation of the grayscale histogram
    histo1(image, histo, width, height);

    //Variable Initialisation
    int threshold = 0;
    float var_max = 0, prov_tresh = 0;
    unsigned long sum = 0, sumB = 0;
    unsigned long q1 = 0, q2 = 0, m1 = 0, m2 = 0;
    unsigned long N = height * width;

    for(int i = 0; i < 256; i++)
        sum += i  * histo[i];

    for(int j = 0; j < 256; j++)
    {
        //Weight Background
        q1 += histo[j];
        if(q1 == 0)
            continue;
        
        //Weight Foreground
        q2 = N - q1;
        if(q2 == 0)
            break;

        sumB += j * histo[j];
        
        m1 = sumB / q1;             //Mean Background
        m2 = (sum - sumB) / q2;     //Mean Foreground

        //Calculate the Between Class Variance
        prov_tresh = q1 * q2 * (m1 - m2) * (m1 - m2);

        //Check if the new Between Class Variance is the max Variance
        if(prov_tresh > var_max)
        {
            threshold = j;
            var_max = prov_tresh;
        }
    }

    return threshold;
}

//fonction de binarisation

void blackAndWhite(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;

    int seuil = otsu_threshold(image, width, height);
    
    for(int i = 0; i < width; i++)
      {
	for(int j = 0; j < height; j++)
	  {
	    Uint32 pixel = get_pixel(image, i, j);

	    Uint8 r, g, b;
	    SDL_GetRGB(pixel, image->format, &r, &g, &b);

	    if (r > seuil)
	      {
		pixel = SDL_MapRGB(image->format, 255, 255, 255);

		put_pixel(image, i, j, pixel);
	      }

	    else
	      {
		pixel = SDL_MapRGB(image->format, 0, 0, 0);

		put_pixel(image, i, j, pixel);
	      }
	  }
      }
}

//fonction de tri

void sort(int L[], int ind)
{
  for (int i = 0; i < ind; i++)
    {
      for (int j = 0; j < ind - 1; j++)
	{
	  if (L[j + 1] < L[j])
	    {
	      int temp = L[j];
	      L[j] = L[j + 1];
	      L[j + 1] = temp;
	    }
	}
    }
}

//filtre passe-bas utilisant la technique du filte médian

SDL_Surface* filtre(SDL_Surface *image)
{
    SDL_Surface* res = image;
    int width = image->w;
    int height = image->h;

    for(int i = 0; i < width; i++)
      {
	for(int j = 0; j < height; j++)
	  {
	    Uint32 pixel = get_pixel(image, i, j);

	    Uint8 r, g, b;
	    SDL_GetRGB(pixel, image->format, &r, &g, &b);

	    if ((i != 0) && (i != width - 1) && (j != 0) && (j != height - 1))
	      {
		int L[9];

		L[8] = r;
		
		Uint32 pixel0 = get_pixel(image, i - 1, j - 1);

		Uint8 r0, g0, b0;
		SDL_GetRGB(pixel0, image->format, &r0, &g0, &b0);

		L[0] = r0;

		Uint32 pixel1 = get_pixel(image, i - 1, j);

		Uint8 r1, g1, b1;
		SDL_GetRGB(pixel1, image->format, &r1, &g1, &b1);

		L[1] = r1;

		Uint32 pixel2 = get_pixel(image, i - 1, j + 1);

		Uint8 r2, g2, b2;
		SDL_GetRGB(pixel2, image->format, &r2, &g2, &b2);

		L[2] = r2;

		Uint32 pixel3 = get_pixel(image, i, j - 1);

		Uint8 r3, g3, b3;
		SDL_GetRGB(pixel3, image->format, &r3, &g3, &b3);

		L[3] = r3;

		Uint32 pixel4 = get_pixel(image, i, j + 1);

		Uint8 r4, g4, b4;
		SDL_GetRGB(pixel4, image->format, &r4, &g4, &b4);

		L[4] = r4;

		Uint32 pixel5 = get_pixel(image, i + 1, j - 1);

		Uint8 r5, g5, b5;
		SDL_GetRGB(pixel5, image->format, &r5, &g5, &b5);

		L[5] = r5;

		Uint32 pixel6 = get_pixel(image, i + 1, j);

		Uint8 r6, g6, b6;
		SDL_GetRGB(pixel6, image->format, &r6, &g6, &b6);

		L[6] = r6;

		Uint32 pixel7 = get_pixel(image, i + 1, j + 1);

		Uint8 r7, g7, b7;
		SDL_GetRGB(pixel7, image->format, &r7, &g7, &b7);

		L[7] = r7;

		sort(L, 9);

		int med = L[4];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }

	    else if ((i == 0) && (j != 0) && (j != height - 1))
	      {
		int L[6];

		L[5] = r;

		Uint32 pixel3 = get_pixel(image, i, j - 1);

		Uint8 r3, g3, b3;
		SDL_GetRGB(pixel3, image->format, &r3, &g3, &b3);

		L[0] = r3;

		Uint32 pixel4 = get_pixel(image, i, j + 1);

		Uint8 r4, g4, b4;
		SDL_GetRGB(pixel4, image->format, &r4, &g4, &b4);

		L[1] = r4;

		Uint32 pixel5 = get_pixel(image, i + 1, j - 1);

		Uint8 r5, g5, b5;
		SDL_GetRGB(pixel5, image->format, &r5, &g5, &b5);

		L[2] = r5;

		Uint32 pixel6 = get_pixel(image, i + 1, j);

		Uint8 r6, g6, b6;
		SDL_GetRGB(pixel6, image->format, &r6, &g6, &b6);

		L[3] = r6;

		Uint32 pixel7 = get_pixel(image, i + 1, j + 1);

		Uint8 r7, g7, b7;
		SDL_GetRGB(pixel7, image->format, &r7, &g7, &b7);

		L[4] = r7;

		sort(L, 6);

		int med = L[3];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }

	    else if ((i == width - 1) && (j != 0) && (j != height - 1))
	      {
	        int L[6];

		L[5] = r;
		
		Uint32 pixel0 = get_pixel(image, i - 1, j - 1);

		Uint8 r0, g0, b0;
		SDL_GetRGB(pixel0, image->format, &r0, &g0, &b0);

		L[0] = r0;

		Uint32 pixel1 = get_pixel(image, i - 1, j);

		Uint8 r1, g1, b1;
		SDL_GetRGB(pixel1, image->format, &r1, &g1, &b1);

		L[1] = r1;

		Uint32 pixel2 = get_pixel(image, i - 1, j + 1);

		Uint8 r2, g2, b2;
		SDL_GetRGB(pixel2, image->format, &r2, &g2, &b2);

		L[2] = r2;

		Uint32 pixel3 = get_pixel(image, i, j - 1);

		Uint8 r3, g3, b3;
		SDL_GetRGB(pixel3, image->format, &r3, &g3, &b3);

		L[3] = r3;

		Uint32 pixel4 = get_pixel(image, i, j + 1);

		Uint8 r4, g4, b4;
		SDL_GetRGB(pixel4, image->format, &r4, &g4, &b4);

		L[4] = r4;

		sort(L, 6);

		int med = L[3];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }

	    else if ((i != 0) && (i != width - 1) && (j == 0))
	      {
		int L[6];

		L[5] = r;
		
		Uint32 pixel1 = get_pixel(image, i - 1, j);

		Uint8 r1, g1, b1;
		SDL_GetRGB(pixel1, image->format, &r1, &g1, &b1);

		L[0] = r1;

		Uint32 pixel2 = get_pixel(image, i - 1, j + 1);

		Uint8 r2, g2, b2;
		SDL_GetRGB(pixel2, image->format, &r2, &g2, &b2);

		L[1] = r2;

	        Uint32 pixel4 = get_pixel(image, i, j + 1);

		Uint8 r4, g4, b4;
		SDL_GetRGB(pixel4, image->format, &r4, &g4, &b4);

		L[2] = r4;

	        Uint32 pixel6 = get_pixel(image, i + 1, j);

		Uint8 r6, g6, b6;
		SDL_GetRGB(pixel6, image->format, &r6, &g6, &b6);

		L[3] = r6;

		Uint32 pixel7 = get_pixel(image, i + 1, j + 1);

		Uint8 r7, g7, b7;
		SDL_GetRGB(pixel7, image->format, &r7, &g7, &b7);

		L[4] = r7;

		sort(L, 6);

		int med = L[3];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }

	    else if ((i != 0) && (i != width - 1) && (j == height - 1))
	      {
		int L[6];

		L[5] = r;
		
		Uint32 pixel0 = get_pixel(image, i - 1, j - 1);

		Uint8 r0, g0, b0;
		SDL_GetRGB(pixel0, image->format, &r0, &g0, &b0);

		L[0] = r0;

		Uint32 pixel1 = get_pixel(image, i - 1, j);

		Uint8 r1, g1, b1;
		SDL_GetRGB(pixel1, image->format, &r1, &g1, &b1);

		L[1] = r1;

	        Uint32 pixel3 = get_pixel(image, i, j - 1);

		Uint8 r3, g3, b3;
		SDL_GetRGB(pixel3, image->format, &r3, &g3, &b3);

		L[2] = r3;

	        Uint32 pixel5 = get_pixel(image, i + 1, j - 1);

		Uint8 r5, g5, b5;
		SDL_GetRGB(pixel5, image->format, &r5, &g5, &b5);

		L[3] = r5;

		Uint32 pixel6 = get_pixel(image, i + 1, j);

		Uint8 r6, g6, b6;
		SDL_GetRGB(pixel6, image->format, &r6, &g6, &b6);

		L[4] = r6;

	        sort(L, 6);

		int med = L[3];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }

	    else if ((i == 0) && (j == 0))
	      {
		int L[4];

		L[3] = r;

	        Uint32 pixel4 = get_pixel(image, i, j + 1);

		Uint8 r4, g4, b4;
		SDL_GetRGB(pixel4, image->format, &r4, &g4, &b4);

		L[0] = r4;
		
		Uint32 pixel6 = get_pixel(image, i + 1, j);

		Uint8 r6, g6, b6;
		SDL_GetRGB(pixel6, image->format, &r6, &g6, &b6);

		L[1] = r6;

		Uint32 pixel7 = get_pixel(image, i + 1, j + 1);

		Uint8 r7, g7, b7;
		SDL_GetRGB(pixel7, image->format, &r7, &g7, &b7);

		L[2] = r7;

		sort(L, 4);

		int med = L[2];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }

	    else if ((i == 0) && (j == height - 1))
	      {
		int L[4];

		L[3] = r;
		
		Uint32 pixel3 = get_pixel(image, i, j - 1);

		Uint8 r3, g3, b3;
		SDL_GetRGB(pixel3, image->format, &r3, &g3, &b3);

		L[0] = r3;

		Uint32 pixel5 = get_pixel(image, i + 1, j - 1);

		Uint8 r5, g5, b5;
		SDL_GetRGB(pixel5, image->format, &r5, &g5, &b5);

		L[1] = r5;

		Uint32 pixel6 = get_pixel(image, i + 1, j);

		Uint8 r6, g6, b6;
		SDL_GetRGB(pixel6, image->format, &r6, &g6, &b6);

		L[2] = r6;

	        sort(L, 4);

		int med = L[2];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }

	    else if ((i == width - 1) && (j == 0))
	      {
		int L[4];

		L[3] = r;
		
	        Uint32 pixel1 = get_pixel(image, i - 1, j);

		Uint8 r1, g1, b1;
		SDL_GetRGB(pixel1, image->format, &r1, &g1, &b1);

		L[0] = r1;

		Uint32 pixel2 = get_pixel(image, i - 1, j + 1);

		Uint8 r2, g2, b2;
		SDL_GetRGB(pixel2, image->format, &r2, &g2, &b2);

		L[1] = r2;

	        Uint32 pixel4 = get_pixel(image, i, j + 1);

		Uint8 r4, g4, b4;
		SDL_GetRGB(pixel4, image->format, &r4, &g4, &b4);

		L[2] = r4;

		sort(L, 4);

		int med = L[2];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }

	    else if ((i == width - 1) && (j == height - 1))
	      {
		int L[4];

		L[3] = r;
		
		Uint32 pixel0 = get_pixel(image, i - 1, j - 1);

		Uint8 r0, g0, b0;
		SDL_GetRGB(pixel0, image->format, &r0, &g0, &b0);

		L[0] = r0;

		Uint32 pixel1 = get_pixel(image, i - 1, j);

		Uint8 r1, g1, b1;
		SDL_GetRGB(pixel1, image->format, &r1, &g1, &b1);

		L[1] = r1;

	        Uint32 pixel3 = get_pixel(image, i, j - 1);

		Uint8 r3, g3, b3;
		SDL_GetRGB(pixel3, image->format, &r3, &g3, &b3);

		L[2] = r3;

	        sort(L, 4);

		int med = L[2];

		pixel = SDL_MapRGB(image->format, med, med, med);

		put_pixel(res, i, j, pixel);
	      }
	  }
      }

    return res;
}

//filtre passe-haut utilisant la technique du filte Sobel

SDL_Surface* filtre2(SDL_Surface *image)
{
    SDL_Surface* res = image;
    int width = image->w;
    int height = image->h;

    for(int i = 1; i < width - 1; i++)
      {
	for(int j = 1; j < height - 1; j++)
	  {
	        int Gx = 0;
		int Gy = 0;

	        Uint32 pixel = get_pixel(image, i, j);

	        Uint8 r, g, b;
	        SDL_GetRGB(pixel, image->format, &r, &g, &b);
		
		Uint32 pixel0 = get_pixel(image, i - 1, j - 1);

		Uint8 r0, g0, b0;
		SDL_GetRGB(pixel0, image->format, &r0, &g0, &b0);

		Gx += 1 * r0;
		Gy += (-1) * r0;

		Uint32 pixel1 = get_pixel(image, i - 1, j);

		Uint8 r1, g1, b1;
		SDL_GetRGB(pixel1, image->format, &r1, &g1, &b1);

		Gx += 2 * r1;
		Gy += 0 * r1;

		Uint32 pixel2 = get_pixel(image, i - 1, j + 1);

		Uint8 r2, g2, b2;
		SDL_GetRGB(pixel2, image->format, &r2, &g2, &b2);

		Gx += 1 * r2;
		Gy += 1 * r2;

		Uint32 pixel3 = get_pixel(image, i, j - 1);

		Uint8 r3, g3, b3;
		SDL_GetRGB(pixel3, image->format, &r3, &g3, &b3);

		Gx += 0 * r3;
		Gy += (-2) * r3;

		Uint32 pixel4 = get_pixel(image, i, j + 1);

		Uint8 r4, g4, b4;
		SDL_GetRGB(pixel4, image->format, &r4, &g4, &b4);

		Gx += 0 * r4;
		Gy += 2 * r4;

		Uint32 pixel5 = get_pixel(image, i + 1, j - 1);

		Uint8 r5, g5, b5;
		SDL_GetRGB(pixel5, image->format, &r5, &g5, &b5);

		Gx += (-1) * r5;
		Gy += (-1) * r5;

		Uint32 pixel6 = get_pixel(image, i + 1, j);

		Uint8 r6, g6, b6;
		SDL_GetRGB(pixel6, image->format, &r6, &g6, &b6);

	        Gx += (-2) * r6;
		Gy += 0 * r6;

		Uint32 pixel7 = get_pixel(image, i + 1, j + 1);

		Uint8 r7, g7, b7;
		SDL_GetRGB(pixel7, image->format, &r7, &g7, &b7);

		Gx += (-1) * r7;
		Gy += 1 * r7;

		int G = sqrt(Gx * Gx + Gy * Gy);

		if (G > 255)
		  {
		    G = 255;
		  }

		pixel = SDL_MapRGB(image->format, G, G, G);

		put_pixel(res, i, j, pixel);
	  }
      }

    return res;
}



/*
int main()
{
  SDL_Surface* image_surface;
  SDL_Surface* screen_surface;
    
  init_sdl();

  image_surface = load_image("my_image3.png");
  screen_surface = display_image(image_surface);

  wait_for_keypressed();

  grayscale(image_surface);

  SDL_Surface* image_surface2;

  image_surface2 = filtre(image_surface);

  //SDL_Surface* image_surface3;

  //image_surface3 = filtre2(image_surface2);

  blackAndWhite(image_surface2);
    
  update_surface(screen_surface, image_surface2);

  wait_for_keypressed();

  SDL_FreeSurface(image_surface2);
  SDL_FreeSurface(screen_surface);
}
*/
