#ifndef __NEEDED_H_
#define __NEEDED_H_

#include "../Preprocess/mainFunctions.h"

struct matrix* preprocess(SDL_Surface* image);

SDL_Surface* detection(struct matrix* matrix, SDL_Surface* image);

struct matrix* GetMatrix(char* path);

#endif
