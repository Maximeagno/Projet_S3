// network.c

# include "network.h"

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

void ComputeOutputsN(network net)
{
  layer l = *net.first;
  for (size_t i = 0; i < net.nbLayers - 1; i++)
  {
    layer l2 = *l.next;
    *l.next = ComputeOutputsL(l2);
    l = *l.next;
  }
  for (size_t i = 0; i < net.nbOutputs; i++)
  {
    neuron n = *(l.Neurons + i);
    *(net.outputs + i) = n.output;
  }
}

void SetInputs(network net, double *inputs)
{
  layer l = *net.first;
  for (size_t i = 0; i < net.nbInputs; i++)
  {
    neuron n = *(l.Neurons + i);
    n.sum = *(inputs + i);
    n.output = sigmoid(n.sum);
    *(l.Neurons + i) = n;
  }
  *net.first = l;
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
      printf("   bias %f\n", n.bias);
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
      printf("\toutput: %f\n", n.output);
    }
    l = *l.next;
  }
}

void printInputs(network net)
{
  printf("Network:\n");
  layer l = *net.first;
  for (size_t i = 0; i < net.nbLayers; i++)
  {
    printf(" layer %zu:\n", i+1);
    for (size_t j = 0; j < l.nbNeurons; j++)
    {
      printf("  neuron %zu:\n", j+1);
      neuron n = *(l.Neurons + j);
      printf("\t input = %f\n", n.sum);
    }
    l = *l.next;
  }
}

void printErrors(network net)
{
  printf("Network:\n");
  layer l = *net.first;
  for (size_t i = 0; i < net.nbLayers; i++)
  {
    printf(" layer %zu:\n", i);
    for (size_t k = 0; k < l.nbNeurons; k++)
    {
      printf("  neuron %zu:\n", k);
      neuron n = *(l.Neurons + k);
      printf("\terror: %f\n", n.error);
    }
    l = *l.next;
  }
}

double* cost_derivative (network net, double *out)
{
  double* cost = calloc(net.nbOutputs, sizeof(double));
  for (size_t i = 0; i < net.nbOutputs; i++)
    *(cost+i) = *(net.outputs+i) - *(out+i);
  return cost;
}

void backprop(network net, double *inp, double *out)
{
  SetInputs(net, inp);
  ComputeOutputsN(net);

  layer l = *net.last;
  double *cost = cost_derivative(net, out);
  for (size_t i = 0; i < l.nbNeurons; i++)
  {
    neuron n = *(l.Neurons + i);
    n.error = *(cost + i) * sigmoid_prime(n.output);
    *(l.Neurons + i) = n;
  }

  l = *l.prev;
  for (size_t k = 0; k < net.nbLayers - 2; k++)
  {
    for (size_t i = 0; i < l.nbNeurons; i++)
    {
      neuron n = *(l.Neurons + i);
      double sum = 0;
      layer next = *l.next;

      for (size_t j = 0; j < next.nbNeurons; j++)
      {
        neuron n2 = *(next.Neurons + j);
        sum += n2.error * *(n2.weights + i);
      }
      n.error = sum * sigmoid_prime(n.output);
      *(l.Neurons + i) = n;
    }
    l = *l.prev;
  }
}

void update(network net, double rate, size_t nbEx, double *inpEx,
double *outEx)
{
  //first descent
  layer l = *net.first;
  for (size_t i = 0; i < net.nbLayers; i++)
  {
    for (size_t j = 0; j < l.nbNeurons; j++)
    {
      neuron n = *(l.Neurons + j);
      n.error = 0;
      *(l.Neurons + j) = n;
    }
    l = *l.next;
  }

  //2nd descent
  for (size_t i = 0; i < nbEx; i++)
  {
    double *inp = calloc(net.nbInputs, sizeof(double));
    double *out = calloc(net.nbOutputs, sizeof(double));
    for (size_t j = 0; j < net.nbInputs; j++)
      *(inp + j) = *(inpEx + j + i * net.nbInputs);
    for (size_t j = 0; j < net.nbOutputs; j++)
      *(out + j) = *(outEx + j + i * net.nbOutputs);
    backprop(net, inp, out);
  }

  //3rd descent
  layer prev = *net.first;
  l = *prev.next;
  for (size_t i = 1; i < net.nbLayers; i++)
  {
    for (size_t j = 0; j < l.nbNeurons; j++)
    {
      neuron n = *(l.Neurons + j);
      for (size_t k = 0; k < prev.nbNeurons; k++)
      {
	neuron n2 = *(prev.Neurons + k);
	*(n.weights + k) -= rate * n.error * n2.sum;
      }
      n.bias -= rate * n.error;
      *(l.Neurons + j) = n;
    }
    *prev.next = l;
    prev = l;
    l = *l.next;
  }
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

    SetInputs (net, inp);
    ComputeOutputsN (net);

    double err = 0;
    for (size_t j = 0; j < net.nbOutputs; j++)
      err += absolute(*(out + j) - *(net.outputs + j));
    error += err / net.nbOutputs;
  }
  return error / nbEx;
}

void training (network net, double rate, size_t nbEx, double *inpEx,
double *outEx, size_t epochs)
{
  for (size_t i = 0; i < epochs; i++)
    update(net, rate, nbEx, inpEx, outEx);
}

void freeAll(network net)
{
  layer l = *net.first;
  for (size_t i = 0; i < net.nbLayers; i++)
  {
    for (size_t j = 0; j < l.nbNeurons; j++)
    {
      neuron n = *(l.Neurons + j);
      free(n.weights);
    }
    free(l.Neurons);
    free(l.prev);
    l = *l.next;
  }
  free(net.first);
  free(net.last);
}

char* Save(network net)
{
  char* string = calloc(1000, sizeof(char));
  char* s = calloc(10, sizeof(char));
  char* i = "Network";
  snprintf(s, 10, "%s\n", i);
  snprintf(s, 10, "%zu\n", net.nbLayers);
  string = strcat(string, s);
  layer l = *net.first;
  for (size_t i = 0; i < net.nbLayers; i++)
  {
    sprintf(s, "%zu\n", l.nbNeurons);
    string = strcat(string, s);
    l = *l.next;
  }
  l = *net.first;
  for (size_t i = 1; i < net.nbLayers; i++)
  {
    layer prev = l;
    l = *l.next;
    for (size_t j = 0; j < l.nbNeurons; j++)
    {
      neuron n = *(l.Neurons + j);
      sprintf(s, "%f\n", n.bias);
      string = strcat(string, s);
      for (size_t k = 0; k < prev.nbNeurons; k++)
      {
        sprintf(s, "%f\n", *(n.weights + k));
        string = strcat(string, s);
      }
    }
  }

  string = strcat(string, "\0");
  return string;
}

int GetLine(char *s, char *l)
{
  int i = 0;
  while (*s != '\n')
  {
    *l = *s;
    l++;
    s++;
    i += 1;
  }
  s++;
  *l = '\0';
  return i+1;
}

void ResetString(char *l)
{
  while (*l != '\0')
  {
    *l = '\0';
    l++;
  }
}

network FromList(char *s)
{
  network net;

  while (*s != '\n')
    s++;
  s++;

  char *line = calloc(10, sizeof(char));
  //char *begin = line;
  int i = GetLine(s, line);
  s += i;

  net.nbLayers = (size_t)atoi(line);
  ResetString(line);
  i = GetLine(s, line);
  s += i;
  net.nbInputs = (size_t)atoi(line);
  layer l1 = NewFirst(net.nbInputs);
  *net.first = l1;
  ResetString(line);

  for (size_t i = 1; i < net.nbLayers; i++)
  {
    i = GetLine(s, line);
    s += i;
    size_t nbN = (size_t)atoi(line);
    layer l2 = NewLayer(nbN, l1);
    SetNext(l1, l2);
    ResetString(line);
    l1 = l2;
  }
  net.nbOutputs = l1.nbNeurons;
  l1.next = NULL;
  *net.last = l1;

  l1 = *net.first;
  layer l2 = *l1.next;
  for (size_t compt = 1; compt < net.nbLayers; compt++)
  {
    for (size_t i = 0; i < l2.nbNeurons; i++)
    {
      neuron n = *(l2.Neurons + i);
      i = GetLine(s, line);
      s += i;
      n.bias = atof(line);
      ResetString(line);
      for (size_t k = 0; k < l1.nbNeurons; k++)
      {
        i = GetLine(s, line);
        s += i;
        *(n.weights + k) = atof(line);
        ResetString(line);
      }
      *(l2.Neurons + i) = n;
    }
    l1 = l2;
    l2 = *l2.next;
  }

  net.outputs = calloc(net.nbOutputs, sizeof(double));

  return net;
}
