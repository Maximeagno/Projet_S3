//mainFunctions.c

#include "mainFunctions.h"

struct matrix* preprocess(SDL_Surface* image)
{
  display_image(image);
  image = black_white(grey_level(image));
  display_image(image);
  struct matrix* res = binarization(image);
  return res;
}

SDL_Surface* detection(struct matrix* matrix, SDL_Surface* image)
{
  image = lines(image, 0);//matrix->h / 50);
  image = columns(matrix, image);
  display_image(image);
  return image;
}

struct matrix* copy_matrix(struct matrix* matrix)
{
  unsigned w = matrix->w;
  unsigned h = matrix->h;
  struct matrix* copy = init_matrix(w, h);
  for (unsigned i = 0; i < w * h; i++)
    copy->mat[i] = matrix->mat[i];
  return copy;
}

struct vector* GetVector(char* path)
{
  SDL_Surface* image = load_image(path);

  struct matrix* matrix = preprocess(image);

  image = detection(matrix, image);

  struct vector* vect = blocks_detection(matrix, image);
  

  free_matrix(matrix);
  SDL_FreeSurface(image);
  return vect;
}

