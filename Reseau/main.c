// main.c

# include "network.h"

int main()
{
   //nbLayers, nbInputs, nbOutputs, nbInter
  network net = NewNetwork (3, 2, 1, 2);

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
  double epochs = 50000.0;

  training(net, rate, nbEx, inpEx, outEx, epochs);

  printf("error %f\n", testNetwork (net, nbEx, inpEx, outEx));


//  char *s = Save(net);
//  printf("%s", s);

//printWeightsNetwork(net);

  freeAll(net);
  free(inpEx);
  free(outEx);

  return 0;
}
