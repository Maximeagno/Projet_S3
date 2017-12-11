//class.h

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct neuron {
  double output;
  double *weights;
  double bias;
  double error;
};

struct layer {
  size_t nbNeurons;
  struct neuron *neurons;
};

struct network {
  double rate;
  double error;
  double momentum;
  size_t epochs;
  struct layer *layers;
  size_t nbLayers;
};

double sigmoide(double x);

double absolute(double x);

double sig_prime(double x);

void feedforward(struct network net, double *inputs);

double ComputeErrors(struct network net, double *ouputs);

void initLayers(struct network net);

void updateW(struct network net);

struct network backprop(struct network net, double **inputs, double **outputs, size_t nbEx);

struct network init(size_t nbLayers, size_t nbInputs, size_t nbOutputs, size_t nbIntern);

void test(struct network net, size_t nbEx, double **inputs);

void freeNetwork(struct network net);

#endif
