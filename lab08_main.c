#include <stdio.h>
#include <stdlib.h>

#include "lab08.h"

int main(){

  char op; // operação
  float valor; // valor do elemento
  int pos, pos1, pos2; // posição a ser inserida e posições a serem revertidas

  list *lista =  (list*)malloc(sizeof(list)); // nó cabeça
  lista->next = NULL;
  lista->prev = NULL;
  lista->len = 0;

// chamadas de funções
  do{

    scanf(" %c", &op);

    if(op == 't'){

      break;
    }
    else if(op == 'i'){

      scanf(" %d %f", &pos, &valor);
      insert(&lista, pos, valor);

    }
    else if(op == 'v'){

      scanf(" %d %d", &pos1, &pos2);
      reverter(&lista, pos1, pos2);
    }
    else if(op == 'p'){

      imprimir(&lista);
    }
  } while (1);

  return 0;
}
