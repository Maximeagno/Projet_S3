//main.c

#include "mainRes.h"

void print_CharInputs(size_t nbEx, double** inputs)
{
  for (size_t i = 0; i < nbEx; i++)
  {
    for (size_t j = 0; j < 50; j++)
    {
      for (size_t k = 0; k < 50; k++)
      {
        if (inputs[i][50*j+k])
          printf("1");
        else
          printf(" ");
      }
      printf("\n");
    }
    printf("\n\n");
  }
}

int main()
{
  srand(time(NULL));

/*
  size_t nbEx = 26 + 10 + 26;
  double **inputs = calloc(nbEx, sizeof(double*));
  double **outputs = calloc(nbEx, sizeof(double*));
  nbEx = GetAlphabetMajNum(inputs, outputs);
  //printAlph(inputs, nbEx);

  size_t nbI = 7*5;
  size_t nbO = 26 + 10 + 1;

  struct network net = init(3, nbI, nbO, 10); //3
*/

/*
//XOR
  size_t nbEx = 4;

  double **inputs = calloc(nbEx, sizeof(double*));
  double **outputs = calloc(nbEx, sizeof(double*));
  for (size_t i = 0; i < nbEx; i++)
  {
    inputs[i] = calloc(2, sizeof(double));
    outputs[i] = malloc(sizeof(double));
  }

  inputs[0][0] = 0;
  inputs[0][1] = 0;
  inputs[1][0] = 0;
  inputs[1][1] = 1;
  inputs[2][0] = 1;
  inputs[2][1] = 0;
  inputs[3][0] = 1;
  inputs[3][1] = 1;

  outputs[0][0] = 0;
//  outputs[0][1] = 1;
  outputs[1][0] = 1;
//  outputs[1][1] = 0;
  outputs[2][0] = 1;
//  outputs[2][1] = 0;
  outputs[3][0] = 0;
//  outputs[3][1] = 1;

  struct network net = init(3, 2, 1, 10);




  net = backprop(net, inputs, outputs, nbEx);

  printf("\nafter update, epochs = %zu\n\n", net.epochs);
  test(net, nbEx, inputs);
*/



/*
  Save(net, "network.txt");
  struct network n = Get("network.txt");

  printf("\nafter save\n\n");
  for (size_t i = 0; i < nbEx; i++)
  {
    feedforward(n, inputs[i]);
    printOutAlph(n);
  }*/

/*
  Best(nbEx, nbI, nbO, inputs, outputs);

  struct network best = Get("BestSaved.txt");

  printf("\nafter best\n");
  test(best, nbEx, inputs);
*/

/*
  GetList(1, 35, 26);
  GetList(2, 35, 26);
  GetList(3, 35, 26);
  GetList(4, 35, 26);
*/


  size_t dim = 50*50;

  //from preprocess
  char *path2 = "../../amelie.bertin/Preprocess/Images_test/Text2.jpg"; //3
//  struct matrix *charFirst2 = GetMatrix(path2);
  char *path3 = "../../amelie.bertin/Preprocess/Images_test/Text3.GIF"; //O
//  struct matrix *charFirst3 = GetMatrix(path3);
  char *path5 = "../../amelie.bertin/Preprocess/Images_test/Text5.jpg"; //G
//  struct matrix *charFirst5 = GetMatrix(path5);
  char *path7 = "../../amelie.bertin/Preprocess/Images_test/Text7.gif"; //l
//  struct matrix *charFirst7 = GetMatrix(path7);

  size_t nbEx = 4;
  char **paths = calloc(nbEx, sizeof(char*));
  paths[0] = path2;
  paths[1] = path3;
  paths[2] = path5;
  paths[3] = path7;
  struct matrix **matrixs = calloc(nbEx, sizeof(struct matrix*));
  for (size_t i = 0; i < nbEx; i++)
    matrixs[i] = GetMatrix(paths[i]);

  double **inputs = calloc(nbEx, sizeof(double*));
  double **outputs = calloc(nbEx, sizeof(double*));
  for (size_t i = 0; i < nbEx; i++)
    inputs[i] = calloc(dim, sizeof(double));

  for (size_t i = 0; i < dim; i++)
  {
/*
    if (charFirst2->mat[i])
      inputs[0][i] = 1.0;
    else
      inputs[0][i] = 0.0;

    if (charFirst3->mat[i])
      inputs[1][i] = 1.0;
    else
      inputs[1][i] = 0.0;

    if (charFirst5->mat[i])
      inputs[2][i] = 1.0;
    else
      inputs[2][i] = 0.0;

    if (charFirst7->mat[i])
      inputs[3][i] = 1.0;
    else
      inputs[3][i] = 0.0;*/
    for (size_t k = 0; k < nbEx; k++)
    {
      if (matrixs[k]->mat[i])
        inputs[k][i] = 1.0;
      else
        inputs[k][i] = 0.0;
    }
  }

  print_CharInputs(nbEx, inputs);
 
  size_t nbO = 10 + 26 + 1;
  for (size_t i = 0; i < nbEx; i++)
    outputs[i] = calloc(nbO, sizeof(double));
  outputs[0][3] = 1;
  outputs[1][10 + 'o' - 'a'] = 1;
  outputs[2][10 + 'g' - 'a'] = 1;
  outputs[3][10 + 'l' - 'a'] = 1;
  outputs[3][10 + 26] = 1;

  size_t nbI = dim;

  struct network net = init(3, nbI, nbO, 10); //3

  net = backprop(net, inputs, outputs, nbEx);

  printf("\nafter update, epochs = %zu\n\n", net.epochs);
  test(net, nbEx, inputs);

  //printOutAlph(net);

  for (size_t i = 0; i < nbEx; i++)
  {
    free(matrixs[i]->mat);
    free(matrixs[i]);
  }
  free(matrixs);
  free(paths);

  for (size_t i = 0; i < nbEx; i++)
  {
    free(inputs[i]);
    free(outputs[i]);
  }
  free(inputs);
  free(outputs);
  freeNetwork(net);

  return 0;
}
