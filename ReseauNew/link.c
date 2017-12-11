//link.c

#include "link.h"

void print_CharInputs(size_t nbEx, double** inputs)
{
  for (size_t i = 0; i < nbEx; i++)
  {
    for (size_t j = 0; j < 50; j++)
    {
      for (size_t k = 0; k < 50; k++)
      {
        if (inputs[i][50*j+k])
          printf("1");
        else
          printf(" ");
      }
      printf("\n");
    }
    printf("\n\n");
  }
}

void GetInputs(size_t nbEx, char *path, size_t dim, double **inputs)
{
  //dim = 50x50
  struct vector* vect = GetVector(path);

  for (size_t i = 0; i < nbEx; i++)
    inputs[i] = calloc(dim, sizeof(double));

  for (size_t i = 0; i < dim; i++)
    for (size_t k = 0; k < nbEx; k++)
    {
      if (vect->tab[k]->mat[i])
        inputs[k][i] = 1.0;
      else
        inputs[k][i] = 0.0;
    }

  free_vector(vect);
}

void SetOutputs(size_t nbEx, double **outputs, char *texts)
{
  size_t nbO = 66;

  for (size_t i = 0; i < nbEx; i++)
  {
    outputs[i] = calloc(nbO, sizeof(double));

    if (texts[i] > 47 && texts[i] < 58)
      outputs[i][texts[i] - '0'] = 1;
    else if (texts[i] > 64 && texts[i] < 91)
      outputs[i][10 + texts[i] - 'A'] = 1;
    else if (texts[i] > 96 && texts[i] < 123)
    {
      outputs[i][10 + texts[i] - 'a'] = 1;
      outputs[i][10 + 26] = 1;
    }
    else
      switch(texts[i])
      {
        case '\n':
          outputs[i][37] = 1;
          break;
        case ' ':
          outputs[i][38] = 1;
          break;
        case '.':
          outputs[i][39] = 1;
          break;
        case ',':
          outputs[i][40] = 1;
          break;
        case ':':
          outputs[i][41] = 1;
          break;
        case '!':
          outputs[i][42] = 1;
          break;
        case '?':
          outputs[i][43] = 1;
          break;
        case '-':
          outputs[i][44] = 1;
          break;
        case '+':
          outputs[i][45] = 1;
          break;
        case '*':
          outputs[i][46] = 1;
          break;
        case '/':
          outputs[i][47] = 1;
          break;
        case '\'':
          outputs[i][48] = 1;
          break;
        case '&':
          outputs[i][49] = 1;
          break;
        case '@':
          outputs[i][50] = 1;
          break;
        case '(':
          outputs[i][51] = 1;
          break;
        case ')':
          outputs[i][52] = 1;
          break;
        case '#':
          outputs[i][53] = 1;
          break;
        case '=':
          outputs[i][54] = 1;
          break;
        case '{':
          outputs[i][55] = 1;
          break;
        case '}':
          outputs[i][56] = 1;
          break;
        case '[':
          outputs[i][57] = 1;
          break;
        case ']':
          outputs[i][58] = 1;
          break;
        case '<':
          outputs[i][59] = 1;
          break;
        case '>':
          outputs[i][60] = 1;
          break;
        //€
        case '$':
          outputs[i][61] = 1;
          break;
        case '%':
          outputs[i][62] = 1;
          break;
        //°
        case '_':
          outputs[i][63] = 1;
          break;
        default:
          break;
      }
  }
}

void trainNetwork(size_t nbEx, size_t dim, double **inputs, double **outputs, int saved, char *filename)
{
  srand(time(NULL));

  struct network net;
  if (saved)
    net = Get(filename);
  else
    net = init(3, dim, 66, 130);

  net = backprop(net, inputs, outputs, nbEx);

  if (Save(net, filename))
    printf("pas possible");

  //free
  freeNetwork(net);
}

void trainAll(size_t nbFile, size_t* nbEx, size_t dim, double ***inputs, double ***outputs, int saved, char *filename)
{
  srand(time(NULL));

  struct network net;
  if(saved)
    net = Get(filename);
  else
    net = init(3, dim, 66, 200);

  double err = 1;

  while (err > 0.0005)
  {
    err = 0;
    for (size_t f = 0; f < nbFile; f++)
      net = backprop(net, inputs[f], outputs[f], nbEx[f]);

    for (size_t f = 0; f < nbFile; f++)
    {
      double e = 0;
      for (size_t i = 0; i < nbEx[f]; i++)
      {
        feedforward(net, inputs[f][i]);
        e += ComputeErrors(net, outputs[f][i]);
      }
      err += e / nbEx[f];
    }
    err /= nbFile;
  }

  if (Save(net, filename))
    printf("pas possible");

  freeNetwork(net);
}

//#define nbletters = 20

char* Interface(char* filename, char* network)
{
  size_t nbletters = 20;
  double **inputs = calloc(nbletters, sizeof(double*));
  GetInputs(nbletters, filename, 50*50, inputs);
  return GetStringFromNetwork(nbletters, inputs, network);
}

char* GetStringFromNetwork(size_t nbEx, double **inputs, char *filename)
{
  struct network net = Get(filename);
  char *string = calloc(nbEx, sizeof(char));

  for (size_t ex = 0; ex < nbEx; ex++)
  {
    feedforward(net, inputs[ex]);

    //getchar
    size_t *end = calloc(2, sizeof(size_t));
    int k = 0;
    for (size_t i = 0; i < net.layers[net.nbLayers-1].nbNeurons; i++)
      if (net.layers[net.nbLayers-1].neurons[i].output > 0.8)
        end[k++] = i;
    if (end[0] < 10)
      string[ex] = '0' + (int)end[0];
    else if (end[0] == 'j' - 'a' + 10)
    {
      string[ex] = 'j';
    }
    else if (end[0] < 36)
    {
      if (k > 0 && !end[1])
        string[ex] = (int)end[0] + 65 - 10;
      else
        string[ex] = (int)end[0] + 97 - 10;
    }
    else
      switch (end[0])
      {
        case 37:
          string[ex] = '\n';
          break;
        case 38:
          string[ex] = ' ';
          break;
        case 39:
          string[ex] = '.';
          break;
        case 40:
          string[ex] = ',';
          break;
        case 41:
          string[ex] = ':';
          break;
        case 42:
          string[ex] = '!';
          break;
        case 43:
          string[ex] = '?';
          break;
        case 44:
          string[ex] = '-';
          break;
        case 45:
          string[ex] = '+';
          break;
        case 46:
          string[ex] = '*';
          break;
        case 47:
          string[ex] = '/';
          break;
        case 48:
          string[ex] = '\'';
          break;
        case 49:
          string[ex] = '&';
          break;
        case 50:
          string[ex] = '@';
          break;
        case 51:
          string[ex] = '(';
          break;
        case 52:
          string[ex] = ')';
          break;
        case 53:
          string[ex] = '#';
          break;
        case 54:
          string[ex] = '=';
          break;
        case 55:
          string[ex] = '{';
          break;
        case 56:
          string[ex] = '}';
          break;
        case 57:
          string[ex] = '[';
          break;
        case 58:
          string[ex] = ']';
          break;
        case 59:
          string[ex] = '<';
          break;
        case 60:
          string[ex] = '>';
          break;
        case 61:
          string[ex] = '$';
          break;
        case 62:
          string[ex] = '%';
          break;
        case 63:
          string[ex] = '_';
          break;
        default:
          string[ex] = '&';
          break;
      }

    free(end);
  }

  freeNetwork(net);
  return string;
}
