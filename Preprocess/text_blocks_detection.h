//text_blocks_detection.h

# ifndef __TEXT_BLOCKS_DETECTION_H__
# define __TEXT_BLOCKS_DETECTION_H__

# include "pretraitement.h"
# include "binarization.h"

SDL_Surface* rlsax(SDL_Surface* image, unsigned c);

SDL_Surface* lines(SDL_Surface* image, unsigned c);

SDL_Surface* columns(struct matrix* matrix, SDL_Surface* image);

struct matrix* mat_char(struct matrix* matrix, SDL_Surface* image, 
                        struct matrix* mark, unsigned begx, unsigned begy);

struct vector { unsigned size, capacity; struct matrix** tab; };

struct vector* init_vector(unsigned capacity);

void free_vector(struct vector* vect);

void vector_add(struct vector* vect, struct matrix* elm);

struct vector* blocks_detection(struct matrix* matrix, SDL_Surface* image);

void print_chars(struct matrix* matrix, SDL_Surface* image);

# endif
