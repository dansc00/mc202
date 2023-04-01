#include <stdio.h>
#include <stdlib.h>

#include "lab09.h"

int busca(tree *root, int n){

  tree *aux = root;

  while(aux){ // enquanto aux != NULL

    if (n == aux->data){ // se o n buscado é igual ao indice atual

      return 1;
    }
    else if (n > aux->data){ //se o n buscado é maior que o indice atual, vai pela direita

      aux = aux->d;
    }
    else if (n < aux->data){ //se o n buscado é menor que o indice atual, vai pela esquerda

      aux = aux->e;
    }
  }

  return 0;
}
//------------------------------------------------------------------------------------------------------
int inserir(tree **root, int x){


  if ((*root)->len != 0){

    tree *new = (tree*)malloc(sizeof(tree));
    new->d = NULL;
    new->e = NULL;
    new->data = x;

    if (busca(*root, x) == 0){
      tree *auxp;
      tree *aux = *root;

      while(aux){

        if (x > aux->data){

          auxp = aux;
          aux = aux->d;
        }
        else{

          auxp = aux;
          aux = aux->e;
        }
      }

      if (x > auxp->data){
        auxp->d = new;
      }
      else{
        auxp->e = new;
      }

      ((*root)->len)++;
      return 1;
    }
    else{
        return 0;
    }
  }
  else{

    (*root)->data = x;
    ((*root)->len)++;
  }

  return 0;

}
//------------------------------------------------------------------------------------------------------
int pre_ordem(tree *node){

  if (node){

    printf("%d ", node->data);
    pre_ordem(node->e);
    pre_ordem(node->d);
  }

  return 1;
}
//-------------------------------------------------------------------------------------------------
int pos_ordem(tree *node){

  if (node){

    pos_ordem(node->e);
    pos_ordem(node->d);
    printf("%d ", node->data);
  }

  return 1;
}
//--------------------------------------------------------------------------------------------------
int em_ordem(tree *node){

  if (node){

    em_ordem(node->e);
    printf("%d ", node->data);
    em_ordem(node->d);
  }

  return 1;
}
//------------------------------------------------------------------------------------------------
int largura(tree *root){

  tree *fila = (tree*)malloc((root->len-1)*sizeof(tree));

  tree* aux = root;
  int fila_len = 0;
  int ind_fila = 0;
  enfileirar(fila, aux, fila_len);

  while (ind_fila <= root->len){

    enfileirar(fila, aux->e, fila_len++);
    enfileirar(fila, aux->d, fila_len++);

    ind_fila++;
    *aux = fila[ind_fila];
  }
  printf("\n");

  free(fila);
  return 0;
}

int enfileirar(tree *fila, tree *node, int fila_len){

    fila[fila_len] = *node;
    printf("%d ", node->data);

  return 0;

}
