//main.c

# include "mainFunctions.h"

int main(int argc, char *argv[])
{
  init_sdl();
  if (argc == 2)
  {
    char *path = argv[1];

    struct vector* res = GetVector(path);
    for (unsigned i = 0; i < 15; i++)
    {
      print_matrix(res->tab[i]);
      printf("\n");
    }

    free_vector(res);

    return 0;
  }
  return 1;
}
