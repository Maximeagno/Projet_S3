//add.c

#include "add.h"
#define SIZE 50

//trend: erreur à mettre sur les poids = somme erreur
//modifier poids après tous les ex avec momentum

int Save(struct network net, char *fichier)
{
//procedure: nbL, nbNeurons pour chaque layer, biais, weights de chaque neuron
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
//  printf("%s", line);
  fscanf(file, "%lf\n", &(n.error));
  fscanf(file, "%zu\n", &(n.epochs));
  fscanf(file, "%lf\n", &(n.rate));
  fscanf(file, "%lf\n", &(n.momentum));
  fscanf(file, "%zu\n", &n.nbLayers);
//  printf("nblayers = %zu\n", n.nbLayers);

  n.layers = calloc(n.nbLayers, sizeof(struct layer));
  for (size_t l = 0; l < n.nbLayers; l++)
  {
    fscanf(file, "%zu\n", &(n.layers[l].nbNeurons));
    n.layers[l].neurons = calloc(n.layers[l].nbNeurons, sizeof(struct neuron));
//    printf("layer %zu: %zu neurons\n", l, n.layers[l].nbNeurons);
  }

  for (size_t l = 1; l < n.nbLayers; l++)
    for (size_t i = 0; i < n.layers[l].nbNeurons; i++)
    {
      fscanf(file, "%lf\n", &(n.layers[l].neurons[i].bias));
      n.layers[l].neurons[i].weights = calloc(n.layers[l-1].nbNeurons, sizeof(double));
      for (size_t j = 0; j < n.layers[l-1].nbNeurons; j++)
        fscanf(file, "%lf\n", &(n.layers[l].neurons[i].weights[j]));
    }

  int err = fclose(file); //0 si OK

  return n;
}

static void initWeights(struct network temp)
{
  //init weights
  for (size_t l = 1; l < temp.nbLayers; l++)
    for (size_t i = 0; i < temp.layers[l].nbNeurons; i++)
      for (size_t j = 0; j < temp.layers[l-1].nbNeurons; j++)
        temp.layers[l].neurons[i].weights[j] = 2*((double)rand()/(double)RAND_MAX - 0.5);
}
/*
void Best(size_t nbEx, size_t nbI, size_t nbO, double **inputs, double **outputs)
{
  FILE *file = NULL;
  char *filename = "best.txt";
  file = fopen(filename, "r");
  struct network net;
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



*
//change nbInt
  size_t nbIntP = nbInt*2;
  size_t nbIntM = nbInt/2;

  struct network plus = init(3, nbI, nbO, nbIntP);
  backprop(net, inputs, outputs, nbEx);

  struct network moins = init(3, nbI, nbO, nbIntM);
  backprop(net, inputs, outputs, nbEx);

  struct network save;

  while (nbIntP != nbIntM)
  {
    struct network end;
    if (plus.epochs < moins.epochs)
      end = plus;
    else
      end = moins;
    if (end.epochs < net.epochs)
    {
      save = net;
      if (moins.epochs < plus.epochs)
      {
        moins = //2 - long
        plus = //2 + mid
      }
      else
      {
        moins = //3 - mid
        plus = //3 + long
      }
    }
    else //net = min
    {
      save = end;
      nbIntP = net.layers[1].nbNeurons + (end.layers[1].nbNeurons + net.layers[1].nbNeurons)/2;
      nbIntM = net.layers[1].nbNeurons - (end.layers[1].nbNeurons + net.layers[1].nbNeurons)/2;
    }

    plus = init(3, nbI, nbO, nbIntP);
    moins = init(3, nbI, nbO, nbIntM);
    backprop(moins, inputs, outputs, nbEx);
    backprop(plus, inputs, outputs, nbEx);
  }
*


  struct network saved = net;
printf("\nEpochs of saved : %zu\n\n", saved.epochs);


*
//boucle rate
  double rate = 0.01;
  for (size_t i = 0; i < 100; i++)
  {
    struct network temp = saved;

    initWeights(temp);

    temp.rate = rate;
    rate += 0.01;

    temp = backprop(temp, inputs, outputs, nbEx);

    if (temp.epochs < saved.epochs && temp.epochs > 20)
      saved = temp;
  }
printf("\nfin rate, rate = %lf, epochs saved = %zu\n\n", saved.rate, saved.epochs);
test(saved, nbEx, inputs);
printf("\n\n");
*

//boucle nbLayers
  size_t nbLayers = saved.nbLayers;
  for (size_t nbl = 0; nbl < 5; nbl++)
  {
    //new network with new nbLayers
    struct network temp2 = saved;

    temp2.nbLayers = nbLayers;
    temp2.layers = realloc(temp2.layers, nbLayers * sizeof(struct layer));

    //temp2.layers[temp2.nbLayers-1] = temp2.layers[temp2.nbLayers-2];
    if (nbLayers != saved.nbLayers)
    {
      temp2.layers[temp2.nbLayers-1].nbNeurons = temp2.layers[temp2.nbLayers-2].nbNeurons;
    }

    temp2.layers[temp2.nbLayers-2].nbNeurons = 2;
    temp2.layers[temp2.nbLayers-2].neurons = realloc(temp2.layers[temp2.nbLayers-2].neurons, 2 * sizeof(struct neuron));

//printf("nbL = %zu\n", temp2.nbLayers);
//printf("%lf\n", temp2.layers[2].neurons[1].weights[0]);
    for (size_t i = 0; i < temp2.layers[temp2.nbLayers-2].nbNeurons; i++)
    {
      temp2.layers[temp2.nbLayers-2].neurons[i].output = 0;
      temp2.layers[temp2.nbLayers-2].neurons[i].bias = 2* ((double)rand() / (double)RAND_MAX - 0.5);
      temp2.layers[temp2.nbLayers-2].neurons[i].weights = realloc(temp2.layers[temp2.nbLayers-2].neurons[i].weights, temp2.layers[temp2.nbLayers-3].nbNeurons * sizeof(double));
      temp2.layers[temp2.nbLayers-2].neurons[i].error = 0;
    }

//printf("%lf\n", temp2.layers[2].neurons[2].weights[0]);
    initWeights(temp2);

printf("OK\n");
    temp2 = backprop(temp2, inputs, outputs, nbEx);


    nbLayers++;


  //boucle nbNeuronsInt
    size_t *nbInt = calloc(temp2.nbLayers-2, sizeof(size_t));
    for (size_t i = 0; i < temp2.nbLayers-2; i++)
      nbInt[i] = 0;
    for (size_t e = 0; e < 200; e++)
    {
      struct network temp = temp2;

      for (size_t l = 1; l < temp.nbLayers-1; l++)
      {
        temp.layers[l].nbNeurons = temp2.layers[l].nbNeurons + nbInt[l-1];
        nbInt[l-1] += 1;
        temp.layers[l].neurons = realloc(temp.layers[l].neurons, temp.layers[l].nbNeurons * sizeof(struct neuron));
        for (size_t i = temp2.layers[l].nbNeurons; i < temp.layers[l].nbNeurons; i++)
        {
          temp.layers[l].neurons[i].output = 0;
          temp.layers[l].neurons[i].bias = 2* ((double)rand() / (double)RAND_MAX - 0.5);

          temp.layers[l].neurons[i].weights = realloc(temp.layers[l].neurons[i].weights, net.layers[l-1].nbNeurons * sizeof(double));
          temp.layers[l].neurons[i].error = 0;
        }
printf("tour et nbInt = %zu\n", nbInt[l-1]);
      }

printf("e = %zu, nbInt = %zu\n", e, temp2.layers[1].nbNeurons + nbInt[0]);

      initWeights(temp);

      temp = backprop(temp, inputs, outputs, nbEx);

      if (temp.epochs < temp2.epochs && temp.epochs > 20)
        temp2 = temp;
    }

printf("OK4\n");

    if (temp2.epochs < saved.epochs && temp2.epochs > 20)
      saved = temp2;
  }

printf("OK5\n");

//boucle momemtum
  double momemtum = 0;
  for (size_t i = 0; i < 20; i++)
  {
    struct network temp = saved;

    initWeights(temp);

    temp.momemtum = momemtum;
    momemtum += 0.0005;

    temp = backprop(temp, inputs, outputs, nbEx);

    if (temp.epochs < saved.epochs && temp.epochs > 20)
    {
      printf("Epochs = %zu\n", temp.epochs);
      saved = temp;
    }
  }

printf("\nfin momemtum, epochs saved = %zu\n\n", saved.epochs);
test(saved, nbEx, inputs);
printf("\n\n");


  Save(saved, filename);
}*/

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

