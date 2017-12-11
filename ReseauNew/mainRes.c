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
  char *path = "../../amelie.bertin/Preprocess/Images_test/Text1-1";
  char *path1 = "../../amelie.bertin/Preprocess/Images_test/Text2";
  char *path2 = "../../amelie.bertin/Preprocess/Images_test/Text3";
  char *path3 = "../../amelie.bertin/Preprocess/Images_test/Text4";
  //char *path4 = "../../amelie.bertin/Preprocess/Images_test/Text5";
  char *path5 = "../../amelie.bertin/Preprocess/Images_test/Text6";
  char *path6 = "../../amelie.bertin/Preprocess/Images_test/Text7";
  char *path10 = "../../amelie.bertin/Preprocess/Images_test/Text10";
  char *path11 = "../../amelie.bertin/Preprocess/Images_test/Text11";
  char *path12 = "../../amelie.bertin/Preprocess/Images_test/Text12";


  size_t nbFile = 12; //7;

  //size_t nbEx = 22;
  //size_t nbEx = 41;
  //size_t nbEx = 52;

  size_t *nbEx = calloc(nbFile, sizeof(size_t));
  nbEx[0] = 136;
  nbEx[1] = 698; //text2
  nbEx[2] = 50;
  nbEx[3] = 300;
  //nbEx[4] = 150;
  nbEx[4] = 150; //text6
  nbEx[5] = 68; //text7
  nbEx[9] = 68; //text7
  nbEx[10] = 68; //text7
  nbEx[11] = 68; //text7

  char **paths = calloc(12, sizeof(char*));
  paths[0] = path;
  paths[1] = path1;
  paths[2] = path2;
  paths[3] = path3;
  //paths[4] = path4;
  paths[4] = path5;
  paths[5] = path6;

  paths[9] = path10;
  paths[10] = path11;
  paths[11] = path12;


  double ***inputs = calloc(nbFile, sizeof(double**));
  double ***outputs = calloc(nbFile, sizeof(double**));
  for (size_t i = 0; i < nbFile; i++)
  {
    inputs[i] = calloc(nbEx[i], sizeof(double*));
    outputs[i] = calloc(nbEx[i], sizeof(double*));
  }


//  for (size_t i = 0; i < nbFile; i++)
//    GetInputs(nbEx[i], paths[i], dim, inputs[i]);
//  print_CharInputs(nbEx, inputs);


  char **texts = calloc(nbFile, sizeof(char*));
  texts[4] = "OCR-A\nABCDEFGHI JKLMNOPQRSTUVWXYZ\nabcdefghi jklmnopqrstuvwxyz\n1234567890\nOC R-B\nABC D E FGH I J KLMNOPQRSTUVWXY Z\nabcdefghi j klmnopqrstuvwxyz\n1 234567890\n";
  //texts[0] = "Thequickbrownfox\njumpedoverthe5\nlazydogs!\n";
  //texts[0] = "Thisisalotof12pointtexttotestthe\nocrcodeandseeifitworksonalltypes\noffileformat.\n";
  //texts[0] = "Onadayofgreatcelebrationandjoy,ontheday\noftheweek,thedayofthemonthof\nintheyeartwothousandswhichcorreponds\n";
  texts[1] = "1 Project Background\nAprescription (R)isawrienorderbya physicianormedicaldoctortoa pharmacistinthermof\nmedication instruions for an individual patient. You can't get prescription medicines unless someone\nwithauthorityprescribesthem. Usually,thismeansawritten prescriptionfromyourdoctor. Dentists,\noptometrists, midwives and nue practitioners may also be authorized to prescribe medicines r you.\nItcan also bedefined as an ordertotake certain medications.\nAprescription haslegal implications;thismeanstheprescribermustassumehis responsibilityforthe\nclinical careofthe patient.\nRecently,theterm \"prescription\" has known a widerusage being usedrclinical assessments,\n";
  //texts[0] = "Last week from F riday to Monday we went to Center Parc \"the\n three forests\".\nWe were with Pastrello family.\nOn Friday, we went to the swimming";
  //texts[0] = "I had called upon my friend, Mr. Sherlock Holmes, one day in the\nautumn";
  texts[5] = "His smile.\nHis eyes.\nHis voice.\nHis laugh.\nHis warm.\nHis existence\n";
  //texts[0] = "My Lovely Family\nHello! My name is Ana. I am eight years old";
  texts[0] = "Select Language\nLatvian\nMacedonian\nNorwegian\nPolish\nPortuguese\nRomanian\nRussian\nSerbian\nSlovak\nSpanish\nSwahili\nSwedish\nVietnamese\nWelsh";
  texts[2] = "Text Message\nMonday 13:12\nJeremy Corbyn here. I'm\nrunning for leader to\nbuild a Labour movement\nserious about winning\npower. Will you back me?\nReply YES, NO or\nMAYBE. Or STOP to opt\nout.";
  texts[3] = "A Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789\nA Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
 // texts[4] = "Le Koleos,";

  texts[9] = "";
  texts[10] = "";
  texts[11] = "";


  size_t *nbskip = calloc(nbFile, sizeof(size_t));

//text2
  skipInp(nbEx[1], inputs[1], 44);
  skipInp(nbEx[1], inputs[1], 98);/*
  skipInp(nbEx[1], inputs[1], 132);
  skipInp(nbEx[1], inputs[1], 344);
  skipInp(nbEx[1], inputs[1], 406);
  skipInp(nbEx[1], inputs[1], 669);*/
  nbskip[1] = 1;

//text7
  skipInp(nbEx[5], inputs[5], 51);
  nbskip[5] = 1;
  

  for (size_t i = 0; i < nbFile; i++)
    nbEx[i] -= nbskip[i];

//  for (size_t i = 0; i < nbFile; i++)
//    SetOutputs(nbEx[i], outputs[i], texts[i]);

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
  //trainNetwork(nbEx[2], dim, inputs[2], outputs[2], 0, "training3.txt");
  //trainAll(nbFile, nbEx, dim, inputs, outputs, 0, "trainAll2.txt");


//print chars
struct vector* vect = GetVector(paths[1]);
//skipVect(nbEx[2]+nbskip[2], vect->tab, 51);

skipVect(nbEx[1]+nbskip[1], vect->tab, 44);
skipVect(nbEx[1]+nbskip[1], vect->tab, 98);
skipVect(nbEx[1]+nbskip[1], vect->tab, 120);
skipVect(nbEx[1]+nbskip[1], vect->tab, 326);
skipVect(nbEx[1]+nbskip[1], vect->tab, 388);/*
skipVect(nbEx[1]+nbskip[1], vect->tab, 669);*/

for (size_t i = 565; i < 620; i++)
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

for (size_t i = 0; i < 620; i++)
  printf("%c", texts[1][i]);
printf("\n");
printf("%d\n", vect->size);
free_vector(vect);


/*
  struct network net = Get("trainAll.txt");
  printf("\nafter update, epochs = %zu\n", net.epochs);
  printf("error = %lf\n\n", net.error);
*/
//  printf("%s\n", GetStringFromNetwork(nbEx[2], inputs[2], "training3.txt"));
/*
  feedforward(net, inputs[5]);
  printOutAlph(net);
*/
/*
  for (size_t i = 0; i < nbFile; i++)
  {
    char* string = GetStringFromNetwork(nbEx[i], inputs[i], "trainAll2.txt");
    printf("%s\n", string);
    free(string);
  }
*/

  //printf("%s\n", Interface(paths[1], "trainAll.txt"));
  

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
  free(nbEx);
  free(nbskip);
  //freeNetwork(net);

  return 0;
}
