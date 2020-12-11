#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <SDL.h>
#include "pixel_operations.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
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

//Take a surface and convert it into a grayscaled version into a Matrix

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

void histo1(SDL_Surface *image, int L[])
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

	    L[r] += 1;
	  }
      }
}

int otsu_threshold(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;

    int histo[256];

    for (int i = 0; i < 256; i++)
      {
	histo[i] = 0;
      }
    //Initialisation and creation of the grayscale histogram
    histo1(image, histo);

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

void blackAndWhite(SDL_Surface *image)
{
    int width = image->w;
    int height = image->h;

    int seuil = otsu_threshold(image);
    
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

int main()
{
    SDL_Surface* image_surface;
    SDL_Surface* screen_surface;
    
    init_sdl();

    image_surface = load_image("my_image2.jpg");
    screen_surface = display_image(image_surface);

    wait_for_keypressed();

    grayscale(image_surface);

    blackAndWhite(image_surface);
    
    update_surface(screen_surface, image_surface);

    wait_for_keypressed();

    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen_surface);
}

