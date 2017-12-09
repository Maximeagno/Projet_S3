//binarization.h

# ifndef __BINARIZATION_H__
# define __BINARIZATION_H__

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "pixel-from-image.h"

struct matrix { unsigned w, h; Uint8* mat; };

struct matrix* init_matrix(unsigned w, unsigned h);

void free_matrix(struct matrix* matrix);

struct matrix* matrix_init(unsigned w, unsigned h);

struct matrix* binarization(SDL_Surface* image);

struct matrix* resize(struct matrix* matrix);

void print_matrix(struct matrix* matrix);

#endif
