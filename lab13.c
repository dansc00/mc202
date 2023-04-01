#include <stdio.h>
#include <stdlib.h>

#include "lab13.h"

int insere(grafo **g, int i, int j, int pos){

  while((*g)->e[pos] != 0 && pos != (n-1)*(i)){

    pos++;
  }

  (*g)->e[pos] = j;
  (*g)->v[i-1] = pos;

  (*g)->e[(n-1)*(j-1)] = i;
  (*g)->v[j-1] = (n-1)*(j-1);  

  else{

    while()
  }




}
