#include <stdio.h>
#include <stdlib.h>

#include "lab06.h"


int main(){

  int n, r, elem; // elem = elementos de requisição

  scanf(" %d", &n); // n de chaves
  scanf(" %d", &r); // n de requisições

  int req[r]; // vetor de requisições

  for(int i = 0; i < r; i++){ // cria vetor de requisições

    scanf(" %d", &elem);
    req[i] = elem;
  }

  celula *top = NULL; // inicializa lista

  add(&top, n); // cria lista

  //mtf(top, req, r); // move to front

  tr(top, req, r); // transpose

  return 0;
}
