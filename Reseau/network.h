// network.h

# include "layer.h"
# include <stdio.h>
# include <string.h>

typedef struct 
{
  size_t nbInputs;
  size_t nbOutputs;
  size_t nbLayers;
  layer *first;
  layer *last;
  double *outputs;
} network;

//create a network
network NewNetwork (size_t nbL, size_t nbI, size_t nbO, size_t nbInt);

//compute outputs of the network
void ComputeOutputsN (network net);

//set inputs of the network on the first layer
void SetInputs (network net, double *inputs);

//print functions
void printWeightsNetwork (network net);
void printOutputs (network net);
void printErrors (network net);

//compute errors
double *cost_derivative (network net, double *out);

//backpropagation: propagation of error
void backprop (network net, double *inp, double *out);

//compute and update new weights
void update (network net, double rate, size_t nbEx, double *inpEx,
double *outEx);

//compute outputs of the network for an example
double testNetwork (network net, size_t nbEx, double *inpEx, double *outEx);

//training the network
void training (network net, double rate, size_t nbEx, double *inpEx,
double *outEx, size_t epochs);

//free memory
void freeAll(network net);

//convert a string to a network
network FromList(char *s);

//convert a network to a string
char* Save(network net);
