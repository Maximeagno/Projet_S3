//text_blocks_detection.c

# include "text_blocks_detection.h"

SDL_Surface* lines(SDL_Surface* image, unsigned c)
{
  unsigned w = (unsigned)(image->w);
  unsigned h = (unsigned)(image->h);
  unsigned start = 0;
  unsigned count = 0;
  for (unsigned n = 0; n < w; n++)
  {
    unsigned nb = 0;
    for (unsigned j = 0; j < h; j++)
    {
      if (GetPixel(image, n, j) == 0)
        nb++;
    }
    if (nb <= c)
    {
      if (count > 0)
      {
        for (unsigned y = 0; y < h; y++)
        {
          unsigned k = 0;
          Uint32 pixel = 1;
          while ((start + k) < w && k < count && pixel != 0)
          {
            pixel = GetPixel(image, start + k, y);
            k++;
          }
          if (pixel == 0)
            for (unsigned x = 0; x < count; x++)
              PutPixel(image, start +x, y, SDL_MapRGB(image->format, 0, 0, 0));
        }
        count = 0;
      }
    }
    else
    {
      if (count == 0)
        start = n;
      count++;
    }
  }
  return image;
}

SDL_Surface* columns(struct matrix* src, SDL_Surface* image)
{
  for (unsigned x = 0; x < src->w; x++)
  {
    unsigned start = 0;
    unsigned count = 0;
    for (unsigned y = 0; y < src->h; y++)
    {
      Uint32 pixel = GetPixel(image, x, y);
      if (pixel == 0)
      {
        if (count == 0)
          start = y;
        count++;
      }
      else
        if (count > 0)
        {
          int b = 0;
          unsigned i = 0;;
          while (i < count && b == 0)
          {
            if (src->mat[x + (start + i) * src->w] == 1)
              b++;
            i++;
          }
          if (b == 0)
            for (unsigned j = 0; j <= count; j++)
              PutPixel(image,x,start+j,SDL_MapRGB(image->format,255,255,255));
          count = 0;
        }
    }
  }
  return image;
}

struct matrix* mat_char(struct matrix* matrix, SDL_Surface* image, 
                        struct matrix* mark, unsigned begx, unsigned begy)
{
  unsigned w = matrix->w;
  unsigned x = begx;
  unsigned h = matrix->h;
  unsigned y = begy;
  while (x < w && GetPixel(image, x, begy) == 0)
    x++;
  while (y < h && GetPixel(image, begx, y) == 0)
    y++;
  unsigned width = x - begx;
  unsigned height = y - begy;
  struct matrix* mat = init_matrix(width, height);
  for (unsigned j = 0; j < height; j++)
    for (unsigned i = 0; i < width; i++)
    {
      mat->mat[i + j * width] = matrix->mat[(begx + i) + (begy + j) * w];
      mark->mat[(begx + i) + (begy + j) * w] = 1;
    }
  if (width >= w / 5 || height >= h / 5)
  {
    free_matrix(mat);
    return NULL;
  }
  struct matrix* res = resize(mat);
  return res;
}

struct vector* init_vector(unsigned capacity)
{
  struct vector* vect = malloc(sizeof(struct vector));
  vect->size = 0;
  vect->capacity = capacity;
  vect->tab = malloc(capacity * sizeof(struct matrix*));
  return vect;
}

void free_vector(struct vector* vect)
{
  for (unsigned i = 0; i < vect->size; i++)
    free_matrix(vect->tab[i]);
  free(vect->tab);
  free(vect);
}

void vector_add(struct vector* vect, struct matrix* elm)
{
  vect->size++;
  if (vect->size > vect->capacity)
  {
    vect->capacity *= 2;
    vect->tab = realloc(vect->tab, vect->capacity * sizeof(struct matrix));
  }
  vect->tab[vect->size - 1] = elm;
}

/*struct vector* spaces(SDL_Surface* image, unsigned y)
{
  struct vector* vect = init_vector(10);
  Uint8 counting = 0;
  Uint8 count = 0;
  for (unsigned x = 0; x < (unsigned)(image->h); x++)
  {
    if (GetPixel(image, x, y) == 0)
    {
      if(counting == 0)
        counting = 1;
      if (counting == 2)
      {
        counting = 1;
        unsigned i = 0;
        while (i < vect->size && vect->tab[i]->mat[0] != count)
          i++;
        if (i == vect->size)
        {
          struct matrix* space = init_matrix(1, 1);
          space->mat[0] = count;
          vector_add(vect, space);
        }
        count = 0;
      }
    }
    else
    {
      if (counting == 1)
      {
        counting = 2;
        count = 1;
      }
      if (counting == 2)
        count++;
    }
  }
  return vect;
}*/

struct matrix* space()
{
  struct matrix* space = init_matrix(50, 50);
  for (unsigned i = 0; i < 2500; i++)
    space->mat[i] = 0;
  return space;
}

struct matrix* jumpline()
{
  struct matrix* jump = init_matrix(50, 50);
  jump->mat[0] = 1;
  for (unsigned i = 1; i < 2500; i++)
    jump->mat[i] = 0;
  return jump;
}

struct vector* blocks_detection(struct matrix* matrix, SDL_Surface* image)
{
  unsigned w = matrix->w;
  unsigned h = matrix->h;
  struct vector* vect = init_vector(100);
  struct matrix* mark = init_matrix(w, h);
  for (unsigned y = 0; y < h; y++)
  {
    //struct vector* space = spaces(image, y);
    
    unsigned count = 0;
    for (unsigned x = 0; x < w; x++)
      if (GetPixel(image, x, y) == 0 && mark->mat[x + y * w] == 0)
      {
        struct matrix* chara = mat_char(matrix, image, mark, x, y);
        if (chara)
        {
          /*if (count > space->tab[space->size / 2])
          {
            struct matrix* space = space();
            vector_add(vect, space);
          }*/
          vector_add(vect, chara);
        }
        count = 0;
      }
      else
      {
        count++;
      }
    if (count < w)
    {
      struct matrix* jump = jumpline();
      vector_add(vect, jump);
    }
  }
  free_matrix(mark);
  return vect;
}

void print_chars(struct matrix* matrix, SDL_Surface* image)
{
  struct vector* vect = blocks_detection(matrix, image);
  for (unsigned i = 0; i < vect->size; i++)
  {
    print_matrix(vect->tab[i]);
    printf("\n");
  }
  free_vector(vect);
}
