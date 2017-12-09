//main.c

#include "tree.h"
#include <stdio.h>
#include <string.h>

void printTree(struct tree *t, int in, int maxDepth)
{
  if (in < maxDepth)
  {
    for (size_t i = 0; i < in; i++)
      printf("--");
    printf("p%d = %c\n", in, t->data);
    for (size_t i = 0; i < t->nbChildren; i++)
      printTree(t->children[i], in+1, maxDepth);
  }
}

int main()
{

/*
  struct tree *A = CreateTree('_', 0, 0);
  printTree(A, 0);
printf("\n\n");
  Add(A, "element");
  Add(A, "ac");
  Add(A, "abc");
  printTree(A, 0);
printf("\n\n");

/  Remove(A, "ac");
  printTree(A, 0);
  Remove(A, "ac");
  printTree(A, 0);
printf("\n\n");/

  printf("Find a : %d\nFind abc : %d\n", Find(A, "a"), Find(A, "abc"));
  Clear(A);

*/
  struct tree *Dico = FromFile("list_fr.txt", 22500);

  //printTree(Dico, 0, 5);
  char *data = malloc(8 * sizeof(char));
  data[0] = 'a';
  data[1] = 'b';
  data[2] = 'a';
  data[3] = 's';
  data[4] = 'i';
  data[5] = 'i';
  data[6] = 'e';
  data[7] = '\0';
  printf("try : %d\n", Try(Dico, data));
  printf("%s\n", data);

  Clear(Dico);
  free(data);
  return 0;
}
