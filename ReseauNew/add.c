//add.c

#include "add.h"
#define SIZE 50

//trend: erreur à mettre sur les poids = somme erreur
//modifier poids après tous les ex avec momentum

int Save(struct network net, char *fichier)
{
//procedure: error, epochs, rate, momentum, nbL, nbNeurons pour chaque layer, biais, weights de chaque neuron
  FILE *file = NULL;
  file = fopen(fichier, "w");

  if (file == NULL)
  {
    printf("impossible\n");
    return 1;
  }
  fprintf(file, "Network\n");
  fprintf(file, "%lf\n", net.error);
  fprintf(file, "%zu\n", net.epochs);
  fprintf(file, "%lf\n", net.rate);
  fprintf(file, "%lf\n", net.momentum);
  fprintf(file, "%zu\n", net.nbLayers);
  for (size_t i = 0; i < net.nbLayers; i++)
    fprintf(file, "%zu\n", net.layers[i].nbNeurons);

  for (size_t l = 1; l < net.nbLayers; l++)
    for (size_t i = 0; i < net.layers[l].nbNeurons; i++)
    {
      fprintf(file, "%lf\n", net.layers[l].neurons[i].bias);
      for (size_t j = 0; j < net.layers[l-1].nbNeurons; j++)
        fprintf(file, "%lf\n", net.layers[l].neurons[i].weights[j]);
    }

  int err = fclose(file); //0 si OK
  return err;
}

struct network Get(char *fichier)
{
  FILE *file = NULL;
  file = fopen(fichier, "r");

  struct network n;

  if (file == NULL)
  {
    printf("impossible\n");
    return n;
  }

  char line[SIZE] = "";
  fgets(line, SIZE, file);
  fscanf(file, "%lf\n", &(n.error));
  fscanf(file, "%zu\n", &(n.epochs));
  fscanf(file, "%lf\n", &(n.rate));
  fscanf(file, "%lf\n", &(n.momentum));
  fscanf(file, "%zu\n", &n.nbLayers);

  n.layers = calloc(n.nbLayers, sizeof(struct layer));
  for (size_t l = 0; l < n.nbLayers; l++)
  {
    fscanf(file, "%zu\n", &(n.layers[l].nbNeurons));
    n.layers[l].neurons = calloc(n.layers[l].nbNeurons, sizeof(struct neuron));
  }

  for (size_t l = 1; l < n.nbLayers; l++)
    for (size_t i = 0; i < n.layers[l].nbNeurons; i++)
    {
      fscanf(file, "%lf\n", &(n.layers[l].neurons[i].bias));
      n.layers[l].neurons[i].weights = calloc(n.layers[l-1].nbNeurons, sizeof(double));
      for (size_t j = 0; j < n.layers[l-1].nbNeurons; j++)
        fscanf(file, "%lf\n", &(n.layers[l].neurons[i].weights[j]));
    }

  if (fclose(file))
    return n;

  return n;
}

static void initWeights(struct network temp)
{
  for (size_t l = 1; l < temp.nbLayers; l++)
    for (size_t i = 0; i < temp.layers[l].nbNeurons; i++)
      for (size_t j = 0; j < temp.layers[l-1].nbNeurons; j++)
        temp.layers[l].neurons[i].weights[j] = 2*((double)rand()/(double)RAND_MAX - 0.5);
}

int meilleur(struct network new, struct network prev)
{
  if (new.error < 0.0001 && new.epochs < prev.epochs && new.epochs > 5)
    return 1;
  return 0;
}

struct network Boucle(struct network new, double **inputs, double **outputs, size_t nbEx)
{
  initLayers(new);
  new = backprop(new, inputs, outputs, nbEx);
  struct network new2 = new;

  //boucle rate
  for (size_t i3 = 1; i3 < 200; i3++)
  {
    struct network new3 = new2;
    new3.rate = i3 * 0.005;

    initWeights(new3);
    new3 = backprop(new3, inputs, outputs, nbEx);

    //boucle momentum
    for (size_t i4 = 0; i4 < 200; i4++)
    {
      struct network new4 = new3;
      new4.momentum = i4 * 0.0005;

      initWeights(new4);
      new4 = backprop(new4, inputs, outputs, nbEx);

      //boucle same (car weights aleatoires)
      for (size_t i5 = 0; i5 < 10; i5++)
      {
        struct network new5 = new4;

        initWeights(new5);
        new5 = backprop(new5, inputs, outputs, nbEx);
//print
printf("\tsame : epochs = %zu\n", new5.epochs);
//if (new5.epochs < 5)
//break;
        if (meilleur(new5, new4))
          new4 = new5;
      }
//print
printf("   momentum tour %zu: epochs = %zu\n", i4, new4.epochs);
//if (new4.epochs < 5)
//break;
      if (meilleur(new4, new3))
        new3 = new4;
    }
//print
printf("  rate tour %zu: epochs = %zu\n", i3, new3.epochs);
//if (new3.epochs < 5)
//break;
    if (meilleur(new3, new2))
      new2 = new3;
  }
//print
printf(" best : epochs = %zu\n", new2.epochs);

  if (meilleur(new2, new))
    new = new2;

  return new;
}

void Best(size_t nbEx, size_t nbI, size_t nbO, double **inputs, double **outputs)
{
  FILE *file = NULL;
  char *filename = "best.txt";
  file = fopen(filename, "r");
  struct network net;

  //init saved
  if (file)
  {
    fclose(file);
    net = Get(filename);
  }
  else
  {
    fclose(file);
    net = init(3, nbI, nbO, 2);
    net = backprop(net, inputs, outputs, nbEx);
  }

  size_t *results1 = calloc(56, sizeof(size_t));
  size_t *results2 = calloc(784, sizeof(size_t));
  size_t index1 = 0;
  size_t index2 = 0;

  struct network saved = net;
  struct network new = saved;

  //boucle nbLayers hidden
  for (size_t i = 1; i < 3; i++)
  {
    if (meilleur(new, saved))
      saved = new;

    new = init(i+2, saved.layers[0].nbNeurons, saved.layers[saved.nbLayers-1].nbNeurons, 2); //nbInt = 2

    for (size_t nbInt1 = 2; nbInt1 < 30; nbInt1++)
    {
      new.layers[new.nbLayers-2].nbNeurons = nbInt1;

      if (i == 1)
        new = Boucle(new, inputs, outputs, nbEx);

      else
        for (size_t nbInt2 = 2; nbInt2 < 30; nbInt2++)
        {
          new.layers[new.nbLayers-3].nbNeurons = nbInt2;
          new = Boucle(new, inputs, outputs, nbEx);
printf("fin boucle2, nbInt = %zu, epochs = %zu\n", nbInt2, new.epochs);
results2[index2++] = new.epochs;
//getchar();
        }
printf("fin boucle, nbInt = %zu, epochs = %zu\n", nbInt1, new.epochs);
results1[index1++] = new.epochs;
//getchar();
    }
//printf("nbL : epochs = %zu\n", new.epochs);
  }

  if (meilleur(new, saved))
    saved = new;

printf("best saved : nbL = %zu, nbInt1 = %zu, rate = %lf, momentum = %lf, epochs = %zu\n", saved.nbLayers, saved.layers[1].nbNeurons, saved.rate, saved.momentum, saved.epochs);

  Save(saved, "BestSaved2.txt");
}

//best saved pour nbL = 3: nbInt1 = 10, rate = 0.100000, momentum = 0.000000, epochs = 361

