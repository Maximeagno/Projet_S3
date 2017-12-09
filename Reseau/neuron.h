// neuron.h

# include <math.h>
# include <stdlib.h>

typedef struct
{
  double *weights;
  double output;
  double sum;
  double error;
  double bias;
} neuron;

//init a new neuron
neuron NewNeuron(size_t nbInputs, double weight);

//compute the sigmoid
double sigmoid(double s);

//compute the prime derivative of sigmoid
double sigmoid_prime(double s);

//compute the absolute
double absolute(double s);
