#include <stdio.h>
#include <stdlib.h>

#include "lab13.h"

int main(){

  int n, i, j, v, auxi, pos;
  // n = nº de vertices
  // i e j = relação de ligação entre vertice i e j. Minimo 1, máximo n
  // v = vertice onde se iniciará a busca

  grafo* g = (grafo*)malloc(sizeof(grafo)); // aloca grafo

  g->v = (int*)calloc(n, sizeof(int)); // aloca vetor que guarda posição do primeiro vizinho de cada vertice
  g->e = (int*)calloc(((n-1)*n)-1, sizeof(int)) // aloca vetor que guarda os vizinhos de cada vertice 0...n consecutivamente

  do{

    scanf(" %d,%d", &i, &j); // entrada i,j
    pos = (n-1)*(i-1);

    if (i){

      insere(&g, i, j, pos);
    }

  }while(i);

  return 0;
}
