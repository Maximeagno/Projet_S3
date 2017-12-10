//link.h

#ifndef __LINK_H__
#define __LINK_H__

#include "../../amelie.bertin/Preprocess/mainFunctions.h"
#include "alphabet.h"
#include "add.h"
#include "class.h"
#include <time.h>

void print_CharInputs(size_t nbEx, double **inputs);

void GetInputs(size_t nbEx, char *path, size_t dim, double **inputs);

void SetOutputs(size_t nbEx, double **outputs, char *texts);

void trainNetwork(size_t nbEx, size_t dim, double **inputs, double **outputs, int saved, char *filename);

void trainAll(size_t nbFile, size_t* nbEx, size_t dim, double ***inputs, double ***outputs, int saved, char *filename);

char* GetStringFromNetwork(size_t nbEx, double **inputs, char *filename);

#endif
