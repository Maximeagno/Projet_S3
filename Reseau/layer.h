// layer.h

# include "neuron.h"

typedef struct layer
{
  struct layer *prev;
  struct layer *next;
  neuron *Neurons;
  size_t nbNeurons;
} layer;

//init a new layer
layer NewLayer(size_t nbNeurons, layer prev);

//init the first layer
layer NewFirst(size_t nbInputs);

//set the next pointer of a layer
layer SetNext(layer now, layer next);

//compute outputs of a layer
layer ComputeOutputsL(layer l);
