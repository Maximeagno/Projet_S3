//add.h

#ifndef __ADD_H_
#define __ADD_H_

#include "class.h"
#include <stdio.h>
#include <stdlib.h>

int Save(struct network net, char *fichier);

struct network Get(char *fichier);

void Best(size_t nbEx, size_t nbI, size_t nbO, double **inputs, double **outputs);

#endif
