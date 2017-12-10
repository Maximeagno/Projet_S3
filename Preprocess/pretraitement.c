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
  int w = image->w;
  int h = image->h;
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

Uint8 new_color(Uint8 c, float f)
{
  float n = f * (c - 128) + 128;
  if (n <= 0)
    return 0;
  if (n >= 255)
    return 255;
  return (Uint8)n;
}

SDL_Surface* contrast(SDL_Surface* image, int delta)
{
  for (unsigned y = 0; y < (unsigned)(image->h); y++)
  {
    for (unsigned x = 0; x < (unsigned)(image->w); x++)
    {
      float f = (259 * (delta + 255))/(255 * (259 - delta));
      Uint32 pixel = GetPixel(image, x, y);
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      r = new_color(r, f);
      g = new_color(g, f);
      b = new_color(b, f);
      PutPixel(image, x, y, SDL_MapRGB(image->format, r, g, b));
    }
  }
  return image;
}

SDL_Surface* revert(SDL_Surface* image)
{
  for (unsigned y = 0; y < (unsigned)(image->h); y++)
    for (unsigned x = 0; x < (unsigned)(image->w); x++)
    {
      Uint32 pixel = GetPixel(image, x, y);
      Uint8 grey;
      SDL_GetRGB(pixel, image->format, &grey, &grey, &grey);
      grey = 255 - grey;
      PutPixel(image, x, y, SDL_MapRGB(image->format, grey, grey, grey));
    }
  return image;
}

Uint8 average_grey(SDL_Surface* image)
{
  Uint8 average = 0;
  for (unsigned y = 0; y < (unsigned)(image->h); y++)
    for (unsigned x = 0; x < (unsigned)(image->w); x++)
    {
      Uint32 pixel = GetPixel(image, x, y);
      Uint8 grey;
      SDL_GetRGB(pixel, image->format, &grey, &grey, &grey);
      average = (average + grey) / 2;
    }
  if (average <= 128)
    image = revert(image);
  return 127 + average / 5;
}

SDL_Surface* black_white(SDL_Surface* image)
{
  Uint8 average = average_grey(image);
  for (unsigned x = 0; x < (unsigned)(image->w); x++)
    for (unsigned y = 0; y < (unsigned)(image->h); y++)
    {
      Uint32 pixel = GetPixel(image, x, y);
      Uint8 grey;
      SDL_GetRGB(pixel, image->format, &grey, &grey, &grey);
      if (grey > average)
        grey = 255;
      else
        grey = 0;
      pixel = SDL_MapRGB(image->format, grey, grey, grey);
      PutPixel(image, x, y, pixel);
    }
  return image;
}
