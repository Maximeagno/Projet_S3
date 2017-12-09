// pixel-from-image.c

# include "pixel-from-image.h"

static inline
Uint8* pixelref(SDL_Surface *image, unsigned x, unsigned y)
{
  int bytes = image->format->BytesPerPixel;
  return (Uint8*)image->pixels + y * image->pitch + x * bytes;
}

Uint32 GetPixel(SDL_Surface *image, unsigned x, unsigned y)
{
  Uint8 *pixel = pixelref(image, x, y);
  switch(image->format->BytesPerPixel)
  {
    case 1:
      return *pixel;
    case 2:
      return *(Uint16 *)pixel;
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return pixel[0] << 16 | pixel[1] << 8 | pixel[2];
      else
        return pixel[0] | pixel[1] << 8 | pixel[2] << 16;
    case 4:
        return *(Uint32 *)pixel;
  }
  return 0;
}

void PutPixel(SDL_Surface *image, unsigned x, unsigned y, Uint32 pixel)
{
  Uint8 *p = pixelref(image, x, y);
  switch(image->format->BytesPerPixel)
  {
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
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
