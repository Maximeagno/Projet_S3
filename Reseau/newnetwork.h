#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct
{
  double *weights;
  double out;
  double in;
  double error;
} neuron;

typedef struct layer
{
  struct layer *prev;
  struct layer *next;
  neuron *Neurons;
  size_t nbNeurons;
} layer;

typedef struct
{
  size_t nbInputs;
  size_t nbOutputs;
  size_t nbLayers;
  layer *first;
  layer *last;
  double *outputs;
} network;
