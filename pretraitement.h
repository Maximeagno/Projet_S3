// pretraitement.h

# ifndef __PRETRAITEMENT_H__
# define __PRETRAITEMENT_H__

# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "pixel-from-image.h"

void wait_for_keypressed();
void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *image);
SDL_Surface* grey_level(SDL_Surface* image);
SDL_Surface* contrast(SDL_Surface* image);
SDL_Surface* black_white(SDL_Surface* image);

# endif
