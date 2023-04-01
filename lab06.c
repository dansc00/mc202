#include <stdio.h>
#include <stdlib.h>

#include "lab06.h"
//-------------------------------------------------------------------------------
int add(celula **top, int n){

  celula *ult;

  for (int i = 0; i < n; i++){

    celula *new;
    new = (celula*)malloc(sizeof(celula));

    if (*top == NULL){

      *top = new;
      new->next = NULL;
    }
    else{

      ult->next = new;
      new->next = NULL;
    }

    ult = new->next; // ultima posição
  }
  return 0;
}
//--------------------------------------------------------------------------------
int mtf(celula *top, int *req, int r){
  printf("ok");
  int cont = 0;

  for (int i = 0; i < r; i++){
    celula *aux;
    for (int j = 1; j < req[i]; j++){

      aux = top->next;
      cont++;
    }

    top = aux;
    aux->next = top->next;
  }
  printf("%d", cont);

  return 0;
}
//--------------------------------------------------------------------------------
int tr(celula *top, int *req, int r){

  int cont = 0;

  for(int i = 0; i < r; i++){
    celula *aux1;
    for(int j = 1; j < req[i]; j++){

      aux1 = top->next;
      cont++;

    }
    celula *aux2;
    for(int k = 1; k < req[i]-1; k++){

      aux2 = top->next;
    }

    aux1 = aux2;
    aux2 = aux1;
  }

  printf(" %d", cont);

  return 0;

}
