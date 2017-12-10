//binarization.c

# include "binarization.h"

struct matrix* init_matrix(unsigned w, unsigned h)
{
  struct matrix* matrix = malloc(sizeof(struct matrix));
  matrix->w = w;
  matrix->h = h;
  matrix->mat = calloc(w * h, sizeof(Uint8));
  return matrix;
}

void free_matrix(struct matrix* matrix)
{
  free(matrix->mat);
  free(matrix);
}

struct matrix* binarization(SDL_Surface* image)
{
  unsigned h = (unsigned)(image->h);
  unsigned w = (unsigned)(image->w);
  struct matrix* matrix = init_matrix(w, h);
  for (unsigned y = 0; y < h; y++)
    for(unsigned x = 0; x < w; x++)
    {
      unsigned long coord = x + y * w;
      if (GetPixel(image, x, y) == 0)
        matrix->mat[coord] = 1;
      //else
        //matrix->mat[coord] = 0;
    }
  return matrix;
}

struct matrix* resize(struct matrix* matrix)
{
  unsigned w = matrix->w;
  unsigned h = matrix->h;
  struct matrix* resize_y = init_matrix(50, h);
  float coef = 50 / (float)w;
  for (unsigned y = 0; y < h; y++)
    for (unsigned x = 0; x < 50; x++)
      resize_y->mat[x + y * 50] = matrix->mat[(unsigned)(x / coef) + y * w];
  coef = 50 / (float)h;
  struct matrix* res = init_matrix(50, 50);
  for(unsigned j = 0; j < 50; j++)
    for (unsigned i = 0; i < 50; i++)
      res->mat[i + j * 50] = resize_y->mat[i + (unsigned)(j / coef) * 50];
  free_matrix(resize_y);
  free_matrix(matrix);
  return res;
}

void print_matrix(struct matrix* matrix)
{
  unsigned w = matrix->w;
  unsigned h = matrix->h;
  for (unsigned y = 0; y < h; y++)
  {
    for (unsigned x = 0; x < w; x++)
      if (matrix->mat[x + y * w])
        printf("1 ");
      else
        printf("  ");
    printf("\n");
  }
}
