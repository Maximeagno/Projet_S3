//main.c

#include "mainRes.h"

void skipInp(size_t nbEx, double **inputs, size_t index)
{
  for (size_t i = index; i < nbEx-1; i++)
    inputs[i] = inputs[i+1];
}

void skipVect(size_t nbEx, struct matrix **inputs, size_t index)
{
  for (size_t i = index; i < nbEx-1; i++)
    inputs[i] = inputs[i+1];
}

int main()
{
  srand(time(NULL));

/*
  //alphabet sur 35 pixels
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
  outputs[1][0] = 1;
  outputs[2][0] = 1;
  outputs[3][0] = 0;

  struct network net = init(3, 2, 1, 10);
*/


/*
  //train
  net = backprop(net, inputs, outputs, nbEx);

  printf("\nafter update, epochs = %zu\n\n", net.epochs);
  test(net, nbEx, inputs);
*/



/*
  //save and test
  Save(net, "network.txt");
  struct network n = Get("network.txt");

  printf("\nafter save\n\n");
  for (size_t i = 0; i < nbEx; i++)
  {
    feedforward(n, inputs[i]);
    printOutAlph(n);
  }*/

/*
  //find best network
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


//main with preprocess
  size_t dim = 50*50;

  //from preprocess
  char *path = "../../amelie.bertin/Preprocess/Images_test/Text1"; //OCR text
  char *path2 = "../../amelie.bertin/Preprocess/Images_test/Text3";
  char *path1 = "../../amelie.bertin/Preprocess/Images_test/Text2";
  char *path3 = "../../amelie.bertin/Preprocess/Images_test/text-autre1.jpg";
  char *path4 = "../../amelie.bertin/Preprocess/Images_test/text-autre2.jpg";
  char *path5 = "../../amelie.bertin/Preprocess/Images_test/text-autre3.jpg";
  char *path6 = "../../amelie.bertin/Preprocess/Images_test/text-autre4.jpg";


  size_t nbFile = 2;

  //size_t nbEx = 150; //text
  //size_t nbEx = 22;
  //size_t nbEx = 41;
  //size_t nbEx = 52;
  //size_t nbEx = 698;  //text2

  size_t *nbEx = calloc(nbFile, sizeof(size_t));
  nbEx[0] = 150;
  nbEx[1] = 698;

  char **paths = calloc(7, sizeof(char*));
  paths[0] = path;
  paths[1] = path1;
  paths[2] = path2;
  paths[3] = path3;
  paths[4] = path4;
  paths[5] = path5;
  paths[6] = path6;


  double ***inputs = calloc(nbFile, sizeof(double**));
  double ***outputs = calloc(nbFile, sizeof(double**));
  for (size_t i = 0; i < nbFile; i++)
  {
    inputs[i] = calloc(nbEx[i], sizeof(double*));
    outputs[i] = calloc(nbEx[i], sizeof(double*));
  }


//  double **inputs = calloc(nbEx, sizeof(double*));
//  double **outputs = calloc(nbEx, sizeof(double*));



  for (size_t i = 0; i < nbFile; i++)
    GetInputs(nbEx[i], paths[i], dim, inputs[i]);
//  print_CharInputs(nbEx, inputs);


  char **texts = calloc(2, sizeof(char*));
  texts[0] = "OCR-A\nABCDEFGHI JKLMNOPQRSTUVWXYZ\nabcdefghi jklmnopqrstuvwxyz\n1234567890\nOC R-B\nABC D E FGH I J KLMNOPQRSTUVWXY Z\nabcdefghi j klmnopqrstuvwxyz\n1 234567890\n";
  //texts[0] = "Thequickbrownfox\njumpedoverthe5\nlazydogs!\n";
  //texts[0] = "Thisisalotof12pointtexttotestthe\nocrcodeandseeifitworksonalltypes\noffileformat.\n";
  //texts[0] = "Onadayofgreatcelebrationandjoy,ontheday\noftheweek,thedayofthemonthof\nintheyeartwothousandswhichcorreponds\n";
  texts[1] = "1 Project Background\nA prescription (R) isa wrien order by a physician or medical doctorto a pharmacistin therm of\nmedication instruions for an individual patient. You can't get prescription medicines unless someone\nwith authority prescribesthem. Usually, this meansa written prescriptionfrom yourdoctor. Dentists,\noptometrists, midwives and nue practitioners may also be authorized to prescribe medicines r you.\nIt can also be defined as an orderto take certain medications.\nA prescription has legal implications;this meansthe prescriber mustassume his responsibilityforthe\nclinical care ofthe patient.\nRecently,theterm \"prescription\" has known a widerusage being usedrclinical assessments,\n ";
  //texts[0] = "Last week from F riday to Monday we went to Center Parc \"the\n three forests\".\nWe were with Pastrello family.\nOn Friday, we went to the swimming";
  //texts[0] = "I had called upon my friend, Mr. Sherlock Holmes, one day in the\nautumn";
  //texts[0] = "His smile.\nHis eyes.\nHis voice.\nHis laugh.\nHis warmth.\nHis existence.\n";
  //texts[0] = "My Lovely Family\nHello! My name is Ana. I am eight years old";


//text2
  skipInp(nbEx[1], inputs[1], 47);
  skipInp(nbEx[1], inputs[1], 109);
  skipInp(nbEx[1], inputs[1], 132);
  skipInp(nbEx[1], inputs[1], 344);
  skipInp(nbEx[1], inputs[1], 406);
  skipInp(nbEx[1], inputs[1], 669);
  size_t nbskip = 6;

  nbEx[1] -= nbskip;

  for (size_t i = 0; i < nbFile; i++)
    SetOutputs(nbEx[i], outputs[i], texts[i]);

/*
//printOutputs
for (size_t ex = 0; ex < nbEx; ex++)
{
  for (size_t i = 0; i < 10 + 26 + 1; i++)
    if (outputs[ex][i])
    {
      printf("ex %zu: out = ", ex);
      if (i < 10)
        printf("%c", i + '0');
      else if (i < 10+26)
        printf("%c", (int)i + 'a' - 10);
      if (i == 10 + 26)
        printf("miniscule");
      printf("\n");
    }
  printf("\n");
}*/

  //trainNetwork(nbEx, dim, inputs, outputs, 1, "training.txt");
  //trainNetwork(nbEx, dim, inputs, outputs, 0, "training2.txt");
  trainAll(nbFile, nbEx, dim, inputs, outputs, 0, "trainAll.txt");

/*
//print chars
struct vector* vect = GetVector(paths[2]);
skipVect(nbEx, vect->tab, 47);
skipVect(nbEx, vect->tab, 109);
skipVect(nbEx, vect->tab, 132);
skipVect(nbEx, vect->tab, 344);
skipVect(nbEx, vect->tab, 406);
skipVect(nbEx, vect->tab, 669);
nbEx -= 6;
for (size_t i = 620; i < nbEx; i++)
{
  for (size_t k = 0; k < 50; k++)
  {
    for (size_t l = 0; l < 50; l++)
    {
      if (vect->tab[i]->mat[k*50+l])
        printf("1");
      else
        printf(" ");
    }
    printf("\n");
  }
  printf("\n\n");
}
for (size_t i = 0; i < nbEx; i++)
  printf("%c", texts[0][i]);
printf("\n");
printf("%d\n", vect->size);
*/



  struct network net = Get("trainAll.txt");
  printf("\nafter update, epochs = %zu\n", net.epochs);
  printf("error = %lf\n\n", net.error);
/*
  feedforward(net, inputs[5]);
  printOutAlph(net);
*/

  for (size_t i = 0; i < nbFile; i++)
  {
    char* string = GetStringFromNetwork(nbEx[i], inputs[i], "trainAll.txt");
    printf("%s\n", string);
  //  for (size_t j = 0; j < nbEx[i]; j++)
  //    printf("%c", string[j]);
  //  printf("\n\n");
  }

  //free
  free(paths);
  free(texts);

  for (size_t f = 0; f < nbFile; f++)
  {
    for (size_t i = 0; i < nbEx[f]; i++)
    {
      free(inputs[f][i]);
      free(outputs[f][i]);
    }
    free(inputs[f]);
    free(outputs[f]);
  }
  free(inputs);
  free(outputs);
  //free(string);
  freeNetwork(net);

  return 0;
}
