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
/*
  size_t m = 0;
  for (size_t i = 1; i < net.layers[net.nbLayers-1].nbNeurons; i++)
    if (net.layers[net.nbLayers-1].neurons[i].output > net.layers[net.nbLayers-1].neurons[m].output)
      m = i;
  if (m > 9)
    printf("output = %c\n", (int)m + 65 - 10);
  else
    printf("output = %zu\n", m);*/

  size_t *end = calloc(2, sizeof(size_t));
  int k = 0;
  for (size_t i = 0; i < net.layers[net.nbLayers-1].nbNeurons; i++)
    if (net.layers[net.nbLayers-1].neurons[i].output > 0.8)
      end[k++] = i;
  if (end[0] > 9)
  {
    if (k > 0 && !end[1])
      printf("output = %c\n", (int)end[0] + 65 - 10);
    else
      printf("output = %c\n", (int)end[0] + 97 - 10);
  }
  else
    printf("output = %zu\n", end[0]);
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

