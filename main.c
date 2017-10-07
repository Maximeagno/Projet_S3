# include "pretraitement.h"

int main()
{
  init_sdl();
  char *path = ;//à compléter avec "fichier.bmp"
  SDL_Surface* image = load_image(path);
  display_image(image);

  SDL_Surface* imageGrey = grey_level(image);
  display_image(imageGrey);

  SDL_Surface* contras = contrast(imageGrey); //pas important
  display_image(contras);

  SDL_Surface* black = black_white(contras);
  display_image(black);

  SDL_FreeSurface(black);

  return 0;
}
