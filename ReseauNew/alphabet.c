//alphabet.c

#include "alphabet.h"

void printAlph(double **inputs, size_t nbEx)
{
  for (size_t ex = 0; ex < nbEx; ex++)
  {
    for (size_t l = 0; l < 7; l++)
    {
      for (size_t c = 0; c < 5; c++)
      {
        if (inputs[ex][l*5 + c] == 0)
          printf(" ");
        else
          printf("X");
      }
      printf("\n");
    }
    printf("\n");
  }
}

size_t GetAlphabetMajNum(double **inputs, double **outputs)
{
  size_t nbEx = 26 + 10 + 26;
  size_t col = 5;
  size_t lin = 7;

  for (size_t i = 0; i < nbEx; i++)
  {
    inputs[i] = calloc(lin * col, sizeof(double));
    outputs[i] = calloc(nbEx - 25, sizeof(double));
    //outputs[i] = calloc(5, sizeof(double)); //en binaire
  }


  for (size_t i = 0; i < nbEx-26; i++)
    outputs[i][i] = 1;
  for (size_t i = 0; i < 26; i++)
  {
    outputs[i+nbEx-26][10+i] = 1;
    outputs[i+nbEx-26][36] = 1;
  }


/*  for (size_t i = 0; i < nbEx; i++) //en binaire
  {
    size_t x = 2;
    for (size_t j = 0; j < 5; j++, x*=2)
      outputs[i][j] = i%x;
  }*/

  //alphabet
  int A = 10;
  int B = 11;
  int C = 12;
  int D = 13;
  int E = 14;
  int F = 15;
  int G = 16;
  int H = 17;
  int I = 18;
  int J = 19;
  int K = 20;
  int L = 21;
  int M = 22;
  int N = 23;
  int O = 24;
  int P = 25;
  int Q = 26;
  int R = 27;
  int S = 28;
  int T = 29;
  int U = 30;
  int V = 31;
  int W = 32;
  int X = 33;
  int Y = 34;
  int Z = 35;
//min
  int a = 36;
  int b = 37;
  int c = 38;
  int d = 39;
  int e = 40;
  int f = 41;
  int g = 42;
  int h = 43;
  int i = 44;
  int j = 45;
  int k = 46;
  int l = 47;
  int m = 48;
  int n = 49;
  int o = 50;
  int p = 51;
  int q = 52;
  int r = 53;
  int s = 54;
  int t = 55;
  int u = 56;
  int v = 57;
  int w = 58;
  int x = 59;
  int y = 60;
  int z = 61;

//5 * 7

  //nombre
  //0
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[0][i] = 1;
    inputs[0][(lin-1)*col + i] = 1;
    inputs[0][(lin-2-i)*col + i] = 1;
  }
  for (size_t i = 1; i < lin-1; i++)
  {
    inputs[0][i*col] = 1;
    inputs[0][i*col + col-1] = 1;
  }

  //1
  for (size_t i = 0; i < lin; i++)
    inputs[1][i*col + col/2] = 1;
  inputs[1][col+1] = 1;
  for (size_t i = 1; i < col-1; i++)
    inputs[1][(lin-1)*col + i] = 1;

  //2
  for (size_t i = 0; i < col; i++)
    inputs[2][(lin-1)*col + i] = 1;
  for (size_t i = 1; i < col-1; i++)
    inputs[2][i] = 1;
  inputs[2][col] = 1;
  inputs[2][2*col-1] = 1;
  for (size_t i = 0; i < col; i++)
    inputs[2][(lin-1-i)*col + i] = 1;

  //3
  for (size_t i = 0; i < col; i++)
    inputs[3][i] = 1;
  for (size_t i = 1; i < col-1; i++)
    inputs[3][(lin-1)*col+i] = 1;
  inputs[3][2*col-2] = 1;
  inputs[3][(lin-1)*col-1] = 1;
  inputs[3][(lin-2)*col] = 1;
  for (size_t i = 2; i < col; i++)
    inputs[3][i*col+i] = 1;

  //4
  for (size_t i = 0; i < lin; i++)
    inputs[4][i*col + col-2] = 1;
  for (size_t i = 0; i < col; i++)
    inputs[4][i + (lin-3)*col] = 1;
  for (size_t i = 0; i < col-1; i++)
    inputs[4][(3-i)*col + i] = 1;

  //5
  for (size_t i = 0; i < col-1; i++)
  {
    inputs[5][i] = 1;
    inputs[5][2*col+i] = 1;
    inputs[5][(lin-1)*col+i] = 1;
  }
  inputs[5][(lin-1)*col] = 0;
  inputs[5][col] = 1;
  inputs[5][col-1] = 1;
  inputs[5][(lin-2)*col] = 1;
  for (size_t i = 3; i < lin-1; i++)
    inputs[5][i*col + col-1] = 1;

  //6
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[6][i + 3*col] = 1;
    inputs[6][i + (lin-1)*col] = 1;
  }
  for (size_t i = 2; i < lin-1; i++)
    inputs[6][i*col] = 1;
  inputs[6][col+1] = 1;
  inputs[6][2] = 1;
  inputs[6][3] = 1;
  inputs[6][(lin-1)*col-1] = 1;
  inputs[6][(lin-2)*col-1] = 1;

  //7
  for (size_t i = 0; i < col; i++)
    inputs[7][i] = 1;
  for (size_t i = 1; i < col; i++)
    inputs[7][i + (lin-2-i)*col] = 1;
  inputs[7][1 + (lin-1)*col] = 1;
  inputs[7][1 + (lin-2)*col] = 1;

  //8
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[8][i] = 1;
    inputs[8][i+3*col] = 1;
    inputs[8][(lin-1)*col+i] = 1;
  }
  for (size_t i = 1; i < 3; i++)
  {
    inputs[8][i*col] = 1;
    inputs[8][i*col + col-1] = 1;
    inputs[8][(lin-1-i)*col] = 1;
    inputs[8][(lin-1-i)*col + col-1] = 1;
  }

  //9
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[9][i] = 1;
    inputs[9][i + 3*col] = 1;
  }
  for (size_t i = 1; i < lin-2; i++)
    inputs[9][col-1 + i*col] = 1;
  inputs[9][col] = 1;
  inputs[9][2*col] = 1;
  inputs[9][(lin-1)*col+1] = 1;
  inputs[9][(lin-1)*col+2] = 1;
  inputs[9][(lin-2)*col+3] = 1;

  //alphabet
  //A
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[A][i] = 1;
    inputs[A][i + 3*col] = 1;
  }
  for (size_t i = 1; i < lin; i++)
  {
    inputs[A][i*col] = 1;
    inputs[A][i*col + col-1] = 1;
  }

  //B
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[B][i] = 1;
    inputs[B][i + 3*col] = 1;
    inputs[B][i + (lin-1)*col] = 1;
  }
  for (size_t i = 0; i < lin; i++)
    inputs[B][i*col] = 1;
  inputs[B][1*col + col-1] = 1;
  inputs[B][2*col + col-1] = 1;
  inputs[B][4*col + col-1] = 1;
  inputs[B][5*col + col-1] = 1;

  //C
  for (size_t i = 1; i < lin-1; i++)
    inputs[C][i*col] = 1;
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[C][i] = 1;
    inputs[C][i + (lin-1)*col] = 1;
  }
  inputs[C][1*col + col-1] = 1;
  inputs[C][(lin-2)*col + col-1] = 1;

  //D
  for (size_t i = 0; i < lin; i++)
    inputs[D][i*col] = 1;
  for (size_t i = 1; i < lin - 1; i++)
    inputs[D][i*col + col-1] = 1;
  for (size_t i = 1; i < col - 1; i++)
  {
    inputs[D][i] = 1;
    inputs[D][i + (lin-1)*col] = 1;
  }

  //E
  for (size_t i = 0; i < lin; i++)
    inputs[E][i*col] = 1;
  for (size_t i = 1; i < col; i++)
  {
    inputs[E][i] = 1;
    inputs[E][i + col*(lin-1)/2] = 1;
    inputs[E][i + col*(lin-1)] = 1;
  }

  //F
  for (size_t i = 0; i < lin; i++)
    inputs[F][i*col] = 1;
  for (size_t i = 1; i < col; i++)
  {
    inputs[F][i] = 1;
    inputs[F][i + col*(lin-1)/2] = 1;
  }

  //G
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[G][i] = 1;
    inputs[G][i + (lin-1)*col] = 1;
  }
  for (size_t i = 1; i < lin-1; i++)
    inputs[G][i*col] = 1;
  inputs[G][col-1 + col] = 1;
  inputs[G][col-2 + col*(lin-3)] = 1;
  inputs[G][col-1 + col*(lin-3)] = 1;
  inputs[G][col-1 + col*(lin-2)] = 1;

  //H
  for (size_t i = 0; i < lin; i++)
  {
    inputs[H][i*col] = 1;
    inputs[H][i*col + col-1] = 1;
  }
  for (size_t i = 1; i < col-1; i++)
    inputs[H][i + (lin-1)/2*col] = 1;

  //I
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[I][i] = 1;
    inputs[I][(lin-1)*col + i] = 1;
  }
  for (size_t i = 1; i < lin-1; i++)
    inputs[I][(col-1)/2 + i*col] = 1;

  //J
  for (size_t i = (col-1)/2; i < col; i++)
    inputs[J][i] = 1;
  for (size_t i = 1; i < lin-1; i++)
    inputs[J][3*(col-1)/4 + i*col] = 1;
  inputs[J][(lin-2)*col] = 1;
  inputs[J][(lin-1)*col + 1] = 1;
  inputs[J][(lin-1)*col + 2] = 1;

  //K
  for (size_t i = 0; i < lin; i++)
    inputs[K][i*col] = 1;
  for (size_t j = 0; j < (lin-1)/2 + 1; j++)
  {
    inputs[K][1 + j + (j+(lin-1)/2)*col] = 1;
    inputs[K][1 + j + ((lin-1)/2 - j)*col] = 1;
  }

  //L
  for (size_t i = 0; i < lin; i++)
    inputs[L][i*col] = 1;
  for (size_t i = 1; i < col; i++)
    inputs[L][i + (lin-1)*col] = 1;

  //M
  for (size_t i = 0; i < lin; i++)
  {
    inputs[M][i*col] = 1;
    inputs[M][i*col + col-1] = 1;
  }
  for (size_t i = 1; i < (lin-1)/2; i++)
  {
    inputs[M][((lin-1)/2 - i) * (col+1)] = 1;
    inputs[M][((lin-1)/2 - i) * (col-1)] = 1;
  }

  //N
  for (size_t i = 0; i < lin; i++)
  {
    inputs[N][i*col] = 1;
    inputs[N][i*col + col-1] = 1;
  }
  for (size_t i = 1; i < col-1; i++)
    inputs[N][i + (1+i)*col] = 1;

  //O
  for (size_t i = 1; i < lin-1; i++)
  {
    inputs[O][i*col] = 1;
    inputs[O][i*col + col-1] = 1;
  }
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[O][i] = 1;
    inputs[O][i + (lin-1)*col] = 1;
  }

  //P
  for (size_t i = 0; i < lin; i++)
    inputs[P][i*col] = 1;
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[P][i] = 1;
    inputs[P][i + 3*col] = 1;
  }
  inputs[P][col - 1 + col] = 1;
  inputs[P][col - 1 + 2*col] = 1;

  //Q
  for (size_t i = 1; i < lin-1; i++)
    inputs[Q][i*col] = 1;
  for (size_t i = 1; i < col-1; i++)
    inputs[Q][i] = 1;
  inputs[Q][(lin-1)*col + 1] = 1;
  inputs[Q][(lin-1)*col + 2] = 1;
  for (size_t i = 1; i < lin-2; i++)
    inputs[Q][i*col + col-1] = 1;
  inputs[Q][lin*col - 1] = 1;
  inputs[Q][(lin-2)*col + col-2] = 1;
  inputs[Q][(lin-3)*col + col-3] = 1;

  //R
  for (size_t i = 0; i < lin; i++)
    inputs[R][i*col] = 1;
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[R][i] = 1;
    inputs[R][i + 3*col] = 1;
  }
  inputs[R][col - 1 + col] = 1;
  inputs[R][col - 1 + 2*col] = 1;
  for (size_t i = 0; i < 3; i++)
    inputs[R][(lin/2 + i + 1)*col + (col-1)/2 + i] = 1;

  //S
  for (size_t i = 1; i < col; i++)
  {
    inputs[S][i] = 1;
    inputs[S][i-1 + (lin-1)*col] = 1;
  }
  for (size_t i = 1; i < col-1; i++)
    inputs[S][i + (lin-1)/2*col] = 1;
  inputs[S][col] = 1;
  inputs[S][2*col] = 1;
  inputs[S][(lin-2)*col + col-1] = 1;
  inputs[S][(lin-3)*col + col-1] = 1;

  //T
  for (size_t i = 0; i < col; i++)
    inputs[T][i] = 1;
  for (size_t i = 1; i < lin; i++)
    inputs[T][(col-1)/2 + i*col] = 1;

  //U
  for (size_t i = 0; i < lin-1; i++)
  {
    inputs[U][i*col] = 1;
    inputs[U][i*col + col-1] = 1;
  }
  for (size_t i = 1; i < col-1; i++)
    inputs[U][i + (lin-1)*col] = 1;

  //V
  for (size_t i = 0; i <= (lin-1)/2; i++)
  {
    inputs[V][i*col] = 1;
    inputs[V][i*col + col-1] = 1;
  }
  inputs[V][1 + (lin-3)*col] = 1;
  inputs[V][col-2 + (lin-3)*col] = 1;
  inputs[V][1 + (lin-2)*col] = 1;
  inputs[V][col-2 + (lin-2)*col] = 1;
  inputs[V][(col-1)/2 + (lin-1)*col] = 1;

  //W
  for (size_t i = 0; i < lin-1; i++)
  {
    inputs[W][i*col] = 1;
    inputs[W][i*col + col-1] = 1;
  }
  for (size_t i = 1; i < col-1; i++)
    inputs[W][i + (lin-1)*col] = 1;
  inputs[W][(col-1)/2 + (lin-1)*col] = 0;
  for (size_t i = (lin-1)/2; i < lin-1; i++)
    inputs[W][(col-1)/2 + i*col] = 1;

  //X
  inputs[X][0] = 1;
  inputs[X][col-1] = 1;
  inputs[X][(lin-1)*col] = 1;
  inputs[X][(lin-1)*col + col-1] = 1;
  for (size_t i = 0; i < col; i++)
  {
    inputs[X][(1 + i)*col + i] = 1;
    inputs[X][(1 + i)*col + col-1 -i] = 1;
  }

  //Y
  for (size_t i = (lin-1)/2; i < lin; i++)
    inputs[Y][(col-1)/2 + i*col] = 1;
  for (size_t i = 0; i < col/2; i++)
  {
    inputs[Y][(i+1)*col + i] = 1;
    inputs[Y][(i+1)*col + col-1 -i] = 1;
  }
  inputs[Y][0] = 1;
  inputs[Y][col-1] = 1;

  //Z
  for (size_t i = 0; i < col; i++)
  {
    inputs[Z][i] = 1;
    inputs[Z][i + (lin-1)*col] = 1;
  }
  for (size_t i = 0; i < col; i++)
    inputs[Z][(i+1)*col + col-1 - i] = 1;


  //minuscules
  //a
  for (size_t i = 1; i < col-1; i++)
  {
    inputs[a][2*col + i] = 1;
    inputs[a][4*col + i] = 1;
    inputs[a][(lin-1)*col + i] = 1;
  }
  for (size_t i = 3; i < lin; i++)
    inputs[a][i*col + col-1] = 1;
  inputs[a][1 + (lin-2)*col] = 1;
  inputs[a][(lin-3)*col + 1] = 0;

  //b
  for (size_t i = 0; i < lin; i++)
    inputs[b][i*col] = 1;
  for (size_t i = 1; i < 3; i++)
    inputs[b][(lin-1)*col + i] = 1;
  inputs[b][(lin-2)*col + 2] = 1;
  inputs[b][(lin-3)*col + 1] = 1;

  //c
  for (size_t i = 1; i < 3; i++)
  {
    inputs[c][(lin-1)*col + i] = 1;
    inputs[c][(lin-3)*col + i] = 1;
  }
  inputs[c][(lin-2)*col] = 1;
  inputs[c][(lin-1)*col] = 1;

  //d
  for (size_t i = 0; i < lin; i++)
    inputs[d][i*col + 2] = 1;
  for (size_t i = 0; i < 2; i++)
    inputs[d][(lin-1)*col + i] = 1;  
  inputs[d][(lin-2)*col] = 1;
  inputs[d][(lin-3)*col + 1] = 1;

  //e
  for (size_t i = 0; i < col-1; i++)
    inputs[e][4*col + i] = 1;
  for (size_t i = 1; i < 3; i++)
  {
    inputs[e][2*col + i] = 1;
    inputs[e][(lin-1)*col + i] = 1;
  }
  inputs[e][(lin-1)*col + 3] = 1;
  inputs[e][(lin-4)*col + 3] = 1;
  for (size_t i = 3; i < lin-1; i++)
    inputs[e][i*col] = 1;

  //f
  for (size_t i = 1; i < lin; i++)
    inputs[f][i*col] = 1;
  for (size_t i = 1; i < 3; i++)
  {
    inputs[f][i] = 1;
    inputs[f][i + 3*col] = 1;
  }

  //g
  for (size_t i = 1; i < lin-1; i++)
    inputs[g][i*col + 2] = 1;
  for (size_t i = 0; i < 2; i++)
  {
    inputs[g][3*col + i] = 1;
    inputs[g][(lin-1)*col + i] = 1;
  }
  inputs[g][2*col] = 1;
  inputs[g][col + 1] = 1;

  //h
  for (size_t i = 0; i < lin; i++)
    inputs[h][i*col] = 1;
  inputs[h][(lin-1)*col + 2] = 1;
  inputs[h][(lin-2)*col + 2] = 1;
  inputs[h][(lin-3)*col + 1] = 1;

  //i
  for (size_t k = 2; k < lin; k++)
    inputs[i][k*col + 2] = 1;
  inputs[i][3*col + 2] = 0;

  //j
  for (size_t k = 1; k < lin-1; k++)
    inputs[j][k*col + 2] = 1;
  inputs[j][2*col + 2] = 0;
  for (size_t i = 0; i < 2; i++)
    inputs[j][(lin-1)*col + i] = 1;

  //k
  for (size_t i = 0; i < lin; i++)
    inputs[k][i*col] = 1;
  for (size_t j = 0; j < 3; j++)
  {
    inputs[k][1 + j + (j+ lin-3)*col] = 1;
    inputs[k][1 + j + (lin-3 - j)*col] = 1;
  }

  //l
  for (size_t i = 0; i < lin; i++)
    inputs[l][i*col] = 1;
  inputs[l][(lin-1)*col + 1] = 1;

  //m
  for (size_t i = lin-3; i < lin; i++)
  {
    inputs[m][i*col] = 1;
    inputs[m][i*col + 2] = 1;
    inputs[m][i*col + col-1] = 1;
  }
  for (size_t i = 0; i < 2; i++)
    inputs[m][i + (lin-4)*col] = 1;
  inputs[m][3 + (lin-4)*col] = 1;

  //n
  for (size_t i = lin-3; i < lin; i++)
  {
    inputs[n][i*col] = 1;
    inputs[n][i*col + 2] = 1;
  }
  for (size_t i = 0; i < 2; i++)
    inputs[n][i + (lin-4)*col] = 1;

  //o
  for (size_t i = 0; i < 2; i++)
  {
    inputs[o][(lin-4)*col + i + 1] = 1;
    inputs[o][(lin-1)*col + i + 1] = 1;
    inputs[o][(lin-2-i)*col] = 1;
    inputs[o][(lin-2-i)*col + 3] = 1;
  }

  //p
  for (size_t i = 0; i < lin; i++)
    inputs[p][i*col] = 1;
  for (size_t i = 0; i < 2; i++)
    inputs[p][2*col + i+1] = 1;
  inputs[p][col+2] = 1;
  inputs[p][1] = 1;

  //q
  for (size_t i = 0; i < lin; i++)
    inputs[q][i*col + 2] = 1;
  for (size_t i = 0; i < 2; i++)
    inputs[q][2*col + i] = 1;
  inputs[q][col] = 1;
  inputs[q][1] = 1;

  //r
  for (size_t i = 3; i < lin; i++)
    inputs[r][i*col] = 1;
  for (size_t i = 1; i < 3; i++)
    inputs[r][2*col + i] = 1;

  //s
  for (size_t i = 0; i < col-2; i++)
  {
    inputs[s][i + (lin-1)*col] = 1;
    inputs[s][i + (lin-3)*col] = 1;
    inputs[s][i+1 + (lin-5)*col] = 1;
  }
  inputs[s][(lin-2)*col + col-2] = 1;
  inputs[s][(lin-4)*col] = 1;

  //t
  for (size_t i = 0; i < lin-1; i++)
    inputs[t][i*col] = 1;
  for (size_t i = 1; i < 3; i++)
    inputs[t][(lin-1)*col + i] = 1;
  inputs[t][2*col + 1] = 1;

  //u
  for (size_t i = 3; i < lin; i++)
  {
    inputs[u][i*col] = 1;
    inputs[u][i*col + 2] = 1;
  }
  for (size_t i = 1; i < 3; i++)
    inputs[u][(lin-1)*col + i] = 1;

  //v
  for (size_t i = 3; i < lin-1; i++)
  {
    inputs[v][i*col] = 1;
    inputs[v][i*col + 2] = 1;
  }
  inputs[v][(lin-1)*col + 1] = 1;

  //w
  for (size_t i = 3; i < lin-1; i++)
  {
    inputs[w][i*col] = 1;
    inputs[w][i*col + col-1] = 1;
  }
  inputs[w][(lin-1)*col + 1] = 1;
  inputs[w][(lin-1)*col + 3] = 1;
  inputs[w][(lin-2)*col + 2] = 1;

  //x
  for (size_t i = 0; i < 3; i++)
  {
    inputs[x][(lin-1-i)*col + i] = 1;
    inputs[x][(i+lin-3)*col + i] = 1;
  }

  //y
  for (size_t i = 2; i < lin-3; i++)
  {
    inputs[y][i*col] = 1;
    inputs[y][i*col + 2] = 1;
  }
  for (size_t i = 1; i < 3; i++)
  {
    inputs[y][(lin-3)*col + i] = 1;
    inputs[y][i-1 + (lin-1)*col] = 1;
  }
  inputs[y][(lin-2)*col + 2] = 1;

  //z
  for (size_t i = 0; i < 4; i++)
  {
    inputs[z][i + (lin-4)*col] = 1;
    inputs[z][i + (lin-1)*col] = 1;
    inputs[z][i + (lin-i-1)*col] = 1;
  }

  return nbEx;
}

void GetList(size_t nbChar, size_t nbPix, size_t nbLetters)
{
  double **listIn = calloc(26+10, sizeof(double*));
  double **listOut = calloc(26+10, sizeof(double*));
  GetAlphabetMajNum(listIn, listOut);

  double **inp = calloc(nbChar, sizeof(double*));
  double **out = calloc(nbChar, sizeof(double*));
  for (size_t i = 0; i < nbChar; i++)
  {
    inp[i] = calloc(nbPix, sizeof(double));
    out[i] = calloc(nbLetters, sizeof(double));
  }

  switch(nbChar)
  {
    case 1:
      inp[0] = listIn[0];
      out[0] = listOut[0];
      break;
    case 2:
      inp[0] = listIn['e' - 'a']; 
      out[0] = listOut['e' - 'a'];
      inp[1] = listIn['t' - 'a'];
      out[1] = listOut['t' - 'a'];
      break;
    case 3:
      inp[0] = listIn['s' - 'a'];
      out[0] = listOut['s' - 'a'];
      inp[1] = listIn['e' - 'a'];
      out[1] = listOut['e' - 'a'];
      inp[2] = listIn['l' - 'a'];
      out[2] = listOut['l' - 'a'];
      break;
    default:
      for (size_t i = 0; i < nbChar; i++)
      {
        inp[i] = listIn[i];
        out[i] = listOut[i];
      }
      break;
  }


  struct network net = init(3, nbPix, nbLetters, 5);
  net = backprop(net, listIn, listOut, nbLetters);

  char *outputs = calloc(nbChar, sizeof(char));
  for (size_t i = 0; i < nbChar; i++)
  {
    feedforward(net, inp[i]);
    for (size_t k = 0; k < nbLetters; k++)
      if (out[i][k] > 0.7)
        outputs[i] = 'a' + k;
  }
  printf("sortie = %s\n", outputs);
}
