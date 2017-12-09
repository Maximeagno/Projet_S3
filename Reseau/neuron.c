// neuron.c

# include "neuron.h"
#include <stdio.h>

neuron NewNeuron(size_t nbInputs, double weight)
{
  neuron n;
  n.weights = calloc(nbInputs, sizeof(double));
  for (size_t i = 0; i < nbInputs; i++)
    *(n.weights + i) = weight + i * 0.3;
  n.output = 0.0;
  n.sum = 0.0;
  n.error = 1.0;
  n.bias = 1.0;
  return n;
}

double sigmoid(double s)
{
  return 1.0 / (1.0 + (1 / exp(s)));
}

double sigmoid_prime(double s)
{
  double a = exp(-s);
  return a / ((1 + a) * (1 + a));
}

double absolute(double s)
{
  if (s < 0)
    return -s;
  return s;
}
