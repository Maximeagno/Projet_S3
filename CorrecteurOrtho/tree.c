//tree.c

#include "tree.h"
#include <stdio.h>

struct tree *CreateTree(char data, int end, size_t nbChildren)
{
  struct tree *tree = malloc(sizeof(struct tree));
  tree->children = calloc(nbChildren, sizeof(struct tree*));
  tree->nbChildren = nbChildren;
  tree->data = data;
  tree->end = end;
  return tree;
}

static size_t Dichotomie(struct tree *tree, char data)
{
  size_t l = 0;
  size_t r = tree->nbChildren;
  while (l < r)
  {
    size_t m = l + (r - l)/2;
    if (tree->children[m]->data == data)
      return m;
    if (tree->children[m]->data > data)
      r = m;
    else
      l = m+1;
  }
  return r;
}

void Add(struct tree *tree, char *data)
{
  while (*data != '\0')
  {
    size_t k = Dichotomie(tree, *data);
    if (k == tree->nbChildren || tree->children[k]->data != *data)
    {
      tree->children = realloc(tree->children, (tree->nbChildren+1) * sizeof(struct tree));
      tree->children[tree->nbChildren] = CreateTree(*data, 0, 0);
      for (size_t i = tree->nbChildren; i > k; i--)
      {
        struct tree *r = tree->children[i];
        tree->children[i] = tree->children[i-1];
        tree->children[i-1] = r;
      }
      tree->nbChildren++;
    }
    tree = tree->children[k];
    data++;
  }
  tree->end = 1;
}

/*peu d'erreurs, mais des leaks
int Remove(struct tree *tree, char *data)
{
  size_t k = Dichotomie(tree, *data);
  if (k == tree->nbChildren || tree->children[k]->data != *data)
    return 0;
  if (data[1] == '\0')
  {
    if (tree->children[k]->end == 0)
      return 0;
    if (tree->children[k]->nbChildren > 0)
    {
      tree->children[k]->end = 0;
      return 0;
    }
    for (size_t i = k; i < tree->nbChildren-1; i++)
      tree->children[i] = tree->children[i+1];
    tree->nbChildren--;
    free(tree->children[tree->nbChildren]);
    return 1;
  }
  data++;
  int del = Remove(tree->children[k], data);
  if (del == 0)
    return 0;
  if (tree->nbChildren > 1)
  {
    free(tree->children[k]);
    for (size_t i = k; i < tree->nbChildren-1; i++)
      tree->children[i] = tree->children[i+1];
    tree->nbChildren--;
    return 0;
  }
  free(tree->children[0]);
  free(tree->children);
  return 1;
}*/

int Find(struct tree *tree, char *data)
{
  while (*data != '\0')
  {
    size_t k = Dichotomie(tree, *data);
    if (k >= tree->nbChildren || tree->children[k]->data != *data)
      return 0;
    tree = tree->children[k];
    data++;
  }
  return tree->end;
}

int Try(struct tree *tree, char *data) //more difficult
{ //if find == 0
  //double letter
  char *copy = calloc(100, sizeof(char));
  for (size_t i = 0; data[i+1] != '\0'; i++)
  {
    if (data[i] == data[i+1])
    {
      for (size_t k = i; data[k+1] != '\0'; k++)
        copy[k] = data[k+1];

      if (Find(tree, copy))
      {
        for (i+=1; data[i] != '\0'; i++)
          data[i] = data[i+1];
        free(copy);
        return 1;
      }
    }
    copy[i] = data[i];
  }
  free(copy);

  //one wrong letter
  char *copy2 = calloc(100, sizeof(char));
  for (size_t i = 0; data[i] != '\0'; i++)
    copy2[i] = data[i];
  for (size_t i = 0; data[i] != '\0'; i++)
  {
    for (int k = 0; k < 26; k++)
    {
      if ('a' + k == data[i])
        continue;

      copy2[i] = 'a' + k;

      if (Find(tree, copy2))
      {
        data[i] = copy2[i];
        free(copy2);
        return 1;
      }

      copy2[i] = data[i];
    }
  }
  free(copy2);
  return 0;
}

void Clear(struct tree *tree)
{
  for (size_t i = 0; i < tree->nbChildren; i++)
    Clear(tree->children[i]);
  free(tree->children);
  free(tree);
}

struct tree* FromFile(char* filename, int nbWords)
{
  FILE *file = NULL;
  file = fopen(filename, "r");

  struct tree *tree = CreateTree('_', 0, 0);

  if (file)
  {
    char *line = calloc(100, sizeof(char));
    //int ok = 0;
    fscanf(file, "%s\n", line);
    int cmpt = 0;
    while (cmpt < nbWords)
    {
      for (size_t i = 0; i < 100; i++)
      {
        if (line[i] == '\0')
          break;
        if (line[i] >= 'A' && line[i] <= 'Z')
          line[i] = 'A' - line[i] + 'a';
      }
      Add(tree, line);
//      char *line2 = calloc(100, sizeof(char));
      fscanf(file, "%s\n", line);
//      if (strcmp(line, line2)==0)
      cmpt++;
    }
    free(line);
  }

  return tree;
}
