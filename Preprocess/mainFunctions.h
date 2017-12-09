//mainFunctions.h

#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#include "pixel-from-image.h"
#include "pretraitement.h"
#include "binarization.h"
#include "text_blocks_detection.h"

struct matrix* preprocess(SDL_Surface* image);

SDL_Surface* detection(struct matrix* matrix, SDL_Surface* image);

struct vector* GetVector(char* path);

#endif
