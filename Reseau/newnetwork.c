#include "newnetwork.h"

neuron NewNeuron(size_t nbInputs, double weight)
{
  neuron n;
  n.weights = calloc(nbInputs, sizeof(double));
  for (size_t i = 0; i < nbInputs; i++)
    *(n.weights + i) = weight + i * 0.3;
  n.out = 0.0;
  n.in = 0.0;
  n.error = 1.0;
  return n;
}

double sigmoid(double s)
{
  return 1.0 / (1.0 + (1 / exp(s)));
}

double absolute(double s)
{
  if (s > 0)
    return s;
  return -s;
}

layer NewLayer(size_t nbNeurons, layer prev)
{
  layer l;
  l.nbNeurons = nbNeurons;
  l.Neurons = calloc(nbNeurons, sizeof(neuron));
  for (size_t i = 0; i < nbNeurons; i++)
    *(l.Neurons + i) = NewNeuron(prev.nbNeurons, 1 + i*0.5);
  l.prev = malloc(sizeof(layer));
  *l.prev = prev;
  l.next = malloc(sizeof(layer));
  return l;
}

layer NewFirst(size_t nbInputs)
{
  layer l;
  l.Neurons = calloc(nbInputs, sizeof(neuron));
  l.next = malloc(sizeof(layer));
  l.prev = NULL;
  l.nbNeurons = nbInputs;
  for (size_t i = 0; i < nbInputs; i++)
    *(l.Neurons + i) = NewNeuron(0, 1);
  return l;
}

layer SetNext(layer now, layer next)
{
  *now.next = next;
  return now;
}

network NewNetwork (size_t nbL, size_t nbI, size_t nbO, size_t nbInt)
{
  network net;
  net.nbInputs = nbI;
  net.nbOutputs = nbO;
  net.nbLayers = nbL;

  net.first = malloc(sizeof(layer));
  net.last = malloc(sizeof(layer));

  *net.first = NewFirst(nbI);
  layer l = *net.first;
  for (size_t i = 1; i < nbL - 1; i++)
  {
    layer intern = NewLayer(nbInt, l);
    SetNext(l, intern);
    l = intern;
  }
  *net.last = NewLayer(nbO, l);
  SetNext(l, *net.last);
  l = *net.last;
  l.next = NULL;

  net.outputs = calloc(nbO, sizeof(double));

  return net;
}

void printWeightsNetwork(network net)
{
  printf("Network:\n");
  layer l = *net.first;
  printf(" layer 0:\n"); 
  for (size_t i = 0; i < l.nbNeurons; i++)
    printf("  neuron %zu:\n \tno weights\n", i);
  l = *l.next;
  for (size_t i = 1; i < net.nbLayers; i++)
  { 
    printf(" layer %zu:\n", i);
    for (size_t j = 0; j < l.nbNeurons; j++)
    {
      printf("  neuron %zu\n", j);
      neuron n = *(l.Neurons + j);
      layer pre = *l.prev;
      for (size_t k = 0; k < pre.nbNeurons; k++)
        printf("\tweights %zu; %f\n", k, *(n.weights + k));
    }
    l = *l.next;
  }
}

void printOutputs(network net)
{
  printf("Network:\n");
  layer l = *net.first;
  for (size_t i = 0; i < net.nbLayers; i++)
  {
    printf(" layer %zu:\n", i);
    for (size_t k = 0; k < l.nbNeurons; k++)
    {
      printf("  neuron %zu\n", k);
      neuron n = *(l.Neurons + k);
      printf("\toutput: %f\n", n.out);
    }
    l = *l.next;
  }
}

size_t Learning(network net, double *inpEx, double *outEx, size_t nbEx,
double rate, size_t epochs)
{
  srand(time(NULL));
  layer prev = *net.first;
  layer l = *prev.next;
  for (size_t i = 1; i < net.nbLayers; i++)
  {
    for (size_t j = 0; j < l.nbNeurons; j++)
    {
      neuron n = *(l.Neurons + j);
      for (size_t k = 0; k < prev.nbNeurons; k++)
        *(n.weights + k) = (double)rand() / (double)RAND_MAX - 1;
      *(l.Neurons + j) = n;
    }
    prev = l;
    l = *l.next;
  }

  double error = 1.0;
  //size_t compt = 0;
  //while (error > 0.01)
  while (epochs > 0)
  {
    //compt += 1;
    error = 0;
    for (size_t i = 0; i < nbEx; i++)
    {
      double *inp = calloc(net.nbInputs, sizeof(double));
      double *out = calloc(net.nbOutputs, sizeof(double));
      for (size_t j = 0; j < net.nbInputs; j++)
        *(inp + j) = *(inpEx + j + i * net.nbInputs);
      for (size_t j = 0; j < net.nbOutputs; j++)
        *(out + j) = *(outEx + j + i * net.nbOutputs);

      l = *net.first;
      for (size_t k = 0; k < l.nbNeurons; k++)
      {
	neuron n = *(l.Neurons + k);
	n.out = *(inp + k);
        *(l.Neurons + k) = n;
      }

      for (size_t k = 1; k < net.nbLayers; k++)
      {
	prev = l;
	l = *l.next;
	for (size_t j = 0; j < l.nbNeurons; j++)
	{
	  neuron n = *(l.Neurons + j);
	  n.in = 0;
	  for (size_t m = 0; m < prev.nbNeurons; m++)
	  {
	    neuron n2 = *(prev.Neurons + m);
	    n.in += *(n.weights + m) * n2.out;
	  }
	  n.out = sigmoid(n.in);
	  *(l.Neurons + j) = n;
	}
      }

      l = *net.last;
      for (size_t j = 0; j < l.nbNeurons; j++)
      {
	neuron n = *(l.Neurons + j);
	n.error = *(out + j) - n.out;
	error += (n.error);
	*(l.Neurons + j) = n;
      }

      for (size_t k = 1; k < net.nbLayers - 1; k++)
      {
	layer next = l;
	l = *l.prev;
	for (size_t j = 0; j < l.nbNeurons; j++)
	{
	  neuron n = *(l.Neurons + j);
	  n.error = 0;
	  for (size_t m = 0; m < next.nbNeurons; m++)
	  {
	    neuron n2 = *(next.Neurons + m);
	    n.error += *(n2.weights + j) * n2.error;
	  }
	  n.error *= n.out * (1 - n.out);
	  *(l.Neurons + j) = n;
	}
      }

      prev = *net.first;
      l = *prev.next;
      for (size_t k = 1; k < net.nbLayers; k++)
      {
	for (size_t j = 0; j < l.nbNeurons; j++)
	{
	  neuron n = *(l.Neurons + j);
	  for (size_t m = 0; m < prev.nbNeurons; m++)
	  {
	    neuron n2 = *(prev.Neurons + m);
	    *(n.weights + m) += rate * n2.out * n.error;
	  }
	  *(l.Neurons + j) = n;
	}
	prev = l;
	l = *l.next;
      }
    }
    epochs--;
    error /= nbEx;
//printf("error : %f\n", error);
//printf("epochs restantes: %zu\n", epochs);
  }
  return 0;
}

double testNetwork (network net, size_t nbEx, double *inpEx, double *outEx)
{
  double error = 0;
  for (size_t i = 0; i < nbEx; i++)
  {
    double *inp = calloc(net.nbInputs, sizeof(double));
    double *out = calloc(net.nbOutputs, sizeof(double));
    for (size_t j = 0; j < net.nbInputs; j++)
      *(inp + j) = *(inpEx + j + i * net.nbInputs);
    for (size_t j = 0; j < net.nbOutputs; j++)
      *(out + j) = *(outEx + j + i * net.nbOutputs);

    layer l = *net.first;
    for (size_t k = 0; k < l.nbNeurons; k++)
    {
      neuron n = *(l.Neurons + k);
      n.out = *(inp + k);
      *(l.Neurons + k) = n;
    }

    for (size_t k = 1; k < net.nbLayers; k++)
    {
      layer prev = l;
      l = *l.next;
      for (size_t j = 0; j < l.nbNeurons; j++)
      {
        neuron n = *(l.Neurons + j);
        n.in = 0;
        for (size_t m = 0; m < prev.nbNeurons; m++)
        {
          neuron n2 = *(prev.Neurons + m);
          n.in += *(n.weights + m) * n2.out;
        }
        n.out = sigmoid(n.in);
        *(l.Neurons + j) = n;
      }
    }


    double err = 0;
    for (size_t j = 0; j < net.nbOutputs; j++)
      err += absolute(*(out + j) - *(net.outputs + j));
    error += err / net.nbOutputs;
  }
  return error / nbEx;
}

int main()
{
  network net = NewNetwork (3, 2, 1, 3);

  size_t nbEx = 4;
  double *inpEx = calloc(4*2, sizeof(double));
  double *outEx = calloc(4*1, sizeof(double));
  *inpEx = 0.0;
  *(inpEx + 1) = 0.0;
  *(inpEx + 2) = 0.0;
  *(inpEx + 3) = 1.0;
  *(inpEx + 4) = 1.0;
  *(inpEx + 5) = 0.0;
  *(inpEx + 6) = 1.0;
  *(inpEx + 7) = 1.0;
  *outEx = 0.0;
  *(outEx + 1) = 1.0;
  *(outEx + 2) = 1.0;
  *(outEx + 3) = 0.0;

  double rate = 0.5;
  size_t epochs = 100000;
printWeightsNetwork(net);
  Learning(net, inpEx, outEx, nbEx, rate, epochs);
printWeightsNetwork(net);
printf("error : %f\n", testNetwork(net, nbEx, inpEx, outEx));
}
