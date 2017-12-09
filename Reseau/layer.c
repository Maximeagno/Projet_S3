// layer.c

# include "layer.h"

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

layer ComputeOutputsL(layer l) //not on the first layer
{
  layer prev = *l.prev;
  for (size_t i = 0; i < l.nbNeurons; i++)
  {
    neuron n = *(l.Neurons + i);
    double sum = 0;
    for (size_t k = 0; k < prev.nbNeurons; k++)
    {
      neuron n2 = *(prev.Neurons + k);
      sum += n2.output * *(n.weights + k);
      sum += n2.bias;
    }
    n.sum = sum;
    n.output = sigmoid(sum);
    *(l.Neurons + i) = n;
  }
  return l;
}
