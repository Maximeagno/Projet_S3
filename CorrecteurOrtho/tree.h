//tree.h

#ifndef __TREE_H_
#define __TREE_H_

#include <stdlib.h>

struct tree {
  struct tree **children;
  char data;
  int end;
  size_t nbChildren;
};

struct tree* CreateTree(char data, int end, size_t nbChildren);

void Add(struct tree *tree, char *data);

int Remove(struct tree *tree, char *data); //not used

int Find(struct tree *tree, char *data);

int Try(struct tree *tree, char *data); //if not find, try to correct it

void Clear(struct tree *tree);

struct tree* FromFile(char* filename, int nbWords);

#endif
