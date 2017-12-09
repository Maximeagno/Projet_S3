//class.c

#include "class.h"
#include "test.h"
#include "alphabet.h"

double sigmoide(double x)
{
//  return (exp(x) - exp(-x)) / (exp(x) + exp(-x)); //tan
  return 1 / (1 + exp(-x));
}

double absolute(double x)
{
  if (x >= 0)
    return x;
  return -x;
}

double sig_prime(double x)
{
//  return (1 + x) * (1 - x);
  return x * (1 - x);
}

void feedforward(struct network net, double *inputs)
{
  //set inputs
  for (size_t i = 0; i < net.layers[0].nbNeurons; i++)
    net.layers[0].neurons[i].output = inputs[i];

  //forward
  for (size_t i = 1; i < net.nbLayers; i++)
  {
    for (size_t j = 0; j < net.layers[i].nbNeurons; j++)
    {
      double sum = net.layers[i].neurons[j].bias;
      for (size_t k = 0; k < net.layers[i-1].nbNeurons; k++)
        sum += net.layers[i-1].neurons[k].output * net.layers[i].neurons[j].weights[k];
      net.layers[i].neurons[j].output = sigmoide(sum);
    }
  }
}

double ComputeErrors(struct network net, double* outputs)
{
  double error = 0;

  //calcul error du dernier layer
  for (size_t i = 0; i < net.layers[net.nbLayers - 1].nbNeurons; i++)
  {
    double out = net.layers[net.nbLayers-1].neurons[i].output;
    net.layers[net.nbLayers -1].neurons[i].error = (outputs[i] - out);
    double err = net.layers[net.nbLayers -1].neurons[i].error;
    error += absolute(err * err * 0.5 * sig_prime(out));
  }

  //propage l'error
  for (int l = net.nbLayers -2; l > 0; l--)
    for(size_t i = 0; i < net.layers[l].nbNeurons; i++)
    {
      double sum = 0;
      for(size_t j = 0; j < net.layers[l+1].nbNeurons; j++)
        sum += net.layers[l+1].neurons[j].weights[i] * net.layers[l+1].neurons[j].error;
      double out = net.layers[l].neurons[i].output;
      net.layers[l].neurons[i].error = sig_prime(out) * sum;
    }

  return error;
}

void initLayers(struct network net)
{

  net.layers[0].neurons = calloc(net.layers[0].nbNeurons, sizeof(struct neuron));
  for (size_t i = 0; i < net.layers[0].nbNeurons; i++)
  {
    net.layers[0].neurons[i].output = 0;
    net.layers[0].neurons[i].bias = 2* ((double)rand() / (double)RAND_MAX - 0.5);
  }

  for (size_t l = 1; l < net.nbLayers; l++)
  {
    net.layers[l].neurons = calloc(net.layers[l].nbNeurons, sizeof(struct neuron));
    for (size_t i = 0; i < net.layers[l].nbNeurons; i++)
    {
      net.layers[l].neurons[i].output = 0;
      net.layers[l].neurons[i].bias = 2* ((double)rand() / (double)RAND_MAX - 0.5);

      net.layers[l].neurons[i].weights = calloc(net.layers[l-1].nbNeurons, sizeof(double));
      net.layers[l].neurons[i].error = 0;
      for (size_t j = 0; j < net.layers[l-1].nbNeurons; j++)
        net.layers[l].neurons[i].weights[j] = 2* ((double)rand() / (double)RAND_MAX - 0.5);

    }
  }
}

void updateW(struct network net)
{
  //change weights
  for (size_t l = 1; l < net.nbLayers; l++)
    for (size_t i = 0; i < net.layers[l].nbNeurons; i++)
    {
      net.layers[l].neurons[i].bias += net.rate * net.layers[l].neurons[i].error + net.momentum * net.layers[l].neurons[i].bias;
      for (size_t j = 0; j < net.layers[l-1].nbNeurons; j++)
        net.layers[l].neurons[i].weights[j] += net.rate * net.layers[l-1].neurons[j].output * net.layers[l].neurons[i].error + net.momentum * net.layers[l].neurons[i].weights[j];
    }
}

struct network backprop(struct network net, double **inputs, double **outputs, size_t nbEx)
{
  double error = 1;
  size_t epoch = 0;

  while (error > 0.0005)
  {
    error = 0;

    //pour tous les exemples
    for (size_t ex = 0; ex < nbEx; ex++)
    {
      feedforward(net, inputs[ex]);

      error += ComputeErrors(net, outputs[ex]);

      updateW(net);
    }

    error /= nbEx;
    net.error = error;

    epoch += 1;

    if (epoch > 8000)
    {
      printf("error");
      break;
    }
//printf("\terror = %f\n", error);
  }

//  printf("nbepochs = %zu\n", epoch);
  net.epochs = epoch;
  return net;
}

struct network init(size_t nbLayers, size_t nbInputs, size_t nbOutputs, size_t nbIntern)
{
  struct network net;
  net.nbLayers = nbLayers;
  net.layers = calloc(nbLayers, sizeof(struct layer));
  net.error = 1;
  net.epochs = 0;
  net.rate = 0.1;
  net.momentum = 0;

  //init layers
  net.layers[0].nbNeurons = nbInputs;
  for (size_t i = 1; i < nbLayers-1; i++)
    net.layers[i].nbNeurons = nbIntern;
  net.layers[nbLayers - 1].nbNeurons = nbOutputs;

  initLayers(net);
  return net;
}

void test(struct network net, size_t nbEx, double **inputs)
{
  for (size_t i = 0; i < nbEx; i++)
  {
    feedforward(net, inputs[i]);
    printOutAlph(net);
  }
}

void freeNetwork(struct network net)
{
  free(net.layers[0].neurons);
  for (size_t l = 1; l < net.nbLayers; l++)
  {
    for (size_t n = 0; n < net.layers[l].nbNeurons; n++)
      free(net.layers[l].neurons[n].weights);
    free(net.layers[l].neurons);
  }
  free(net.layers);
}
