// pretraitement.c

# include "pretraitement.h"

void wait_for_keypressed()
{
  SDL_Event event;
  for(;;)
  {
    SDL_PollEvent(&event);
    switch (event.type)
    {
      case SDL_KEYDOWN:return;
      default: break;
    }
  }
}

void init_sdl()
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    errx(1, "Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
  SDL_Surface *image;
  image = IMG_Load(path);
  if (!image)
    errx(3, "Can't load %s: %s", path, IMG_GetError());
  return image;
}

SDL_Surface* display_image(SDL_Surface *image)
{
  SDL_Surface *screen;
  /*
  Display* d = XOpenDisplay(NULL);
  Screen* s = DefaultScreenOfDisplay(d);*/
  int w = image->w;
  int h = image->h;
/*
  if (w > (s->height))
    w = (s->height);
  if (h > (s->width))
    h = (s->width);
*/
  screen = SDL_SetVideoMode(w, h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if (!screen)
    errx(1, "Couldn't set %dx%d video mode: %s\n", w, h, SDL_GetError());

  if (SDL_BlitSurface(image, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  SDL_UpdateRect(screen, 0, 0, w, h);

  wait_for_keypressed();

  return screen;
}

SDL_Surface* grey_level(SDL_Surface* image)
{
  for (unsigned x = 0; x < (unsigned)(image->w); x++)
    for (unsigned y = 0; y < (unsigned)(image->h); y++)
    {
      Uint32 pixel = GetPixel(image, x, y);
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      Uint8 grey = 0.3*r + 0.59*g + 0.11*b;
      pixel = SDL_MapRGB(image->format, grey, grey, grey);
      PutPixel(image, x, y, pixel);
    }
  return image;
}

SDL_Surface* contrast(SDL_Surface* image)
{
  Uint8 maxi = 0;
  Uint8 mini = 255;
  for (unsigned x = 0; x < (unsigned)(image->w); x++)
    for (unsigned y = 0; y < (unsigned)(image->h); y++)
    {
      Uint32 pixel = GetPixel(image, x, y);
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      if ((r+g+b)/3 > maxi)
        maxi = (r+g+b)/3;
      if ((r+g+b)/3 < mini)
        mini = (r+g+b)/3;
    }
  Uint8 nvmax = 255;
  for (unsigned x = 0; x < (unsigned)(image->w); x++)
    for (unsigned y = 0; y < (unsigned)(image->h); y++)
    {
      Uint32 pixel = GetPixel(image, x, y);
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      Uint8 nv = ((r+g+b)/3 - mini)*nvmax/maxi;

      Uint8 d = nv/25;
      if (nv%25 > 12)
        d += 1;
      nv = 25 * d;

      pixel = SDL_MapRGB(image->format, nv, nv, nv);
      PutPixel(image, x, y, pixel);
    }
  return image;
}

SDL_Surface* black_white(SDL_Surface* image)
{
  for (unsigned x = 0; x < (unsigned)(image->w); x++)
    for (unsigned y = 0; y < (unsigned)(image->h); y++)
    {
      Uint32 pixel = GetPixel(image, x, y);
      Uint8 r;
      Uint8 g;
      Uint8 b;
      Uint8 black;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      if ((r+g+b)/3 > 255/2)
        black = 255;
      else
        black = 0;
      pixel = SDL_MapRGB(image->format, black, black, black);
      PutPixel(image, x, y, pixel);
    }
  return image;
}
