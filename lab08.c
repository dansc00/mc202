#include <stdio.h>
#include <stdlib.h>

#include "lab08.h"

int insert(list **lista, int pos, double valor){

  list *new = (list*)malloc(sizeof(list)); // novo elemento
  new->next = NULL;
  new->prev = NULL;
  new->data = valor;

  if ((*lista)->len != 0){ // se o primeiro elemento já foi inserido

    //list *auxp = (*lista)->prev;

    if (pos == 0){ // se a inserção é na cabeça

      new->next = *lista;
      (*lista)->prev = new;
      *lista = new;

    }
    else{
      if (pos >= (*lista)->len){ // se a posição buscada está fora do tamanho da lista

        list *aux = *lista; // aux começa na cabeça
        for (int i = 1; i < (*lista)->len; i++){ // insere no fim

          aux = aux->next; // sai ultimo nó
        }

        aux->next = new; // atribui new
        new->prev = aux;

      }
      else if (pos < (*lista)->len){ // se posição está dentro do tamanho da lista

        list *ind = indice(*lista, pos); // retorna o nó no indice buscado
        list *indp = indice(*lista, pos-1); // retorna o nó anterior ao nó no indice buscado

        indp->next = new;
        new->prev = indp;
        new->next = ind;
        ind->prev = new;
      }
    }
  }
  else{ // se o primeiro elemento ainda n foi inserido

    (*lista)->data = new->data;

  }

  ((*lista)->len)++; // aumenta tamanho da lista

  return 0;
}
//-----------------------------------------------------------------------------
int reverter(list **lista, int pos1, int pos2){

  if (pos1 == pos2){

    return 0;
  }

  if (pos1 < pos2){

    list *aux1, *aux2 = *lista;
    //list *auxp1, *auxp2;
    double aux;

    for (int i = 0; i <= pos1; i++){

      //auxp1 = aux1;
      aux1 = aux1->next;
    }

    for (int j = 0; j <= pos2; j++){

      //auxp2 = aux2;
      aux2 = aux2->next;
    }

    aux = aux1->data;
    aux1->data = aux2->data;
    aux2->data = aux;

    return 1;
  }

}

//-----------------------------------------------------------------------------
list* indice(list *lista, int pos){

  list *aux = lista;

  for (int i = 0; i < pos; i++){

    aux = aux->next;
  }

  return aux;

}

//-----------------------------------------------------------------------------
int imprimir(list **lista){

  list *aux = *lista;

  while (aux != NULL){

    printf("%.4f ", aux->data);

    aux = aux->next;

  }

  printf("\n");
  return  0;
}
