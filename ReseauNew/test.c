//test.c

#include "test.h"

void printOuts(struct network net)
{
  printf("network\n");
  for (size_t l = 0; l < net.nbLayers; l++)
  {
    printf(" layer %zu:\n", l);
    for (size_t i = 0; i < net.layers[l].nbNeurons; i++)
      printf("   output %zu = %f\n", i, net.layers[l].neurons[i].output);
  }
}

void printOut(struct network net)
{
  for (size_t i = 0; i < net.layers[net.nbLayers-1].nbNeurons; i++)
    printf("output %zu = %f\n", i, net.layers[net.nbLayers-1].neurons[i].output);
}

void printOutAlph(struct network net)
{
  size_t *end = calloc(2, sizeof(size_t));
  int k = 0;
  for (size_t i = 0; i < net.layers[net.nbLayers-1].nbNeurons; i++)
    if (net.layers[net.nbLayers-1].neurons[i].output > 0.8)
      end[k++] = i;
  if (end[0] < 10)
    printf("output = %zu\n", end[0]);
  else if (end[0] < 36)
  {
    if (k > 0 && !end[1])
      printf("output = %c\n", (int)end[0] + 65 - 10);
    else
      printf("output = %c\n", (int)end[0] + 97 - 10);
  }
  else
    switch (end[0])
    {
      case 37:
        printf("output = \"\\n\" \n");
        break;
      case 38:
        printf("output = ' '\n");
        break;
      case 39:
        printf("output = '.'\n");
        break;
      case 40:
        printf("output = ','\n");
        break;
      case 41:
        printf("output = ':'\n");
        break;
      case 42:
        printf("output = '!'\n");
        break;
      case 43:
        printf("output = '?'\n");
        break;
      case 44:
        printf("output = '-'\n");
        break;
      case 45:
        printf("output = '+'\n");
        break;
      case 46:
        printf("output = '*'\n");
        break;
      case 47:
        printf("output = '/'\n");
        break;
      case 48:
        printf("output = '''\n");
        break;
      case 49:
        printf("output = '&'\n");
        break;
      case 50:
        printf("output = '@'\n");
        break;
      case 51:
        printf("output = '('\n");
        break;
      case 52:
        printf("output = ')'\n");
        break;
      case 53:
        printf("output = '#'\n");
        break;
      case 54:
        printf("output = '='\n");
        break;
      case 55:
        printf("output = '{'\n");
        break;
      case 56:
        printf("output = '}'\n");
        break;
      case 57:
        printf("output = '['\n");
        break;
      case 58:
        printf("output = ']'\n");
        break;
      case 59:
        printf("output = '<'\n");
        break;
      case 60:
        printf("output = '>'\n");
        break;
      case 61:
        printf("output = '$'\n");
        break;
      case 62:
        printf("output = '\%'\n");
        break;
      case 63:
        printf("output = '_'\n");
        break;
      default:
        printf("output = error, char = %c\n", end[0]);
        break;
    }

  free(end);
}

void printOutAlphBin(struct network net)
{
  int x = 0;
  int k = 1;
  for (size_t i = 0; i < net.layers[net.nbLayers-1].nbNeurons; i++, k*=2)
    if (net.layers[net.nbLayers-1].neurons[i].output > 0.9)
      x += k;
  printf("output = %c\n", x + 65);
}

void printWeights(struct network net)
{
  printf("network\n");
  for (size_t l = 1; l < net.nbLayers; l++)
  {
    printf(" layer %zu:\n", l);
    for (size_t j = 0; j < net.layers[l].nbNeurons; j++)
    {
      printf("   neuron %zu:\n", j);
      for (size_t i = 0; i < net.layers[l-1].nbNeurons; i++)
        printf("     weights %zu = %f\n", i, net.layers[l].neurons[j].weights[i]);
    }
  }
}

void printErrors(struct network net)
{
  printf("network\n");
  for (size_t l = 1; l < net.nbLayers; l++)
  {
    printf(" layer %zu:\n", l);
    for (size_t i = 0; i < net.layers[l].nbNeurons; i++)
      printf("   error %zu = %f\n", i, net.layers[l].neurons[i].error);
  }
}
