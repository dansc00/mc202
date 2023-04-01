#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab09.h"

int main(){

  int x, n;
  char op[10];


  tree *root = (tree*)malloc(sizeof(tree)); // inicializa a raiz da arvore
  root->e = NULL;
  root->d = NULL;
  root->len = 0;

  do{

    scanf(" %s", op);

    if (strcmp(op, "terminar") == 0){
      break;
    }
    else if (strcmp(op, "inserir") == 0){

      scanf(" %d", &x);

      inserir(&root, x);
    }
    else if (strcmp(op, "buscar") == 0){

      scanf(" %d", &n);
      if (busca(root, n)){

        printf("%d pertence\n", n);
      }
      else{

        printf("%d nao pertence\n", n);
      }
    }
    else if (strcmp(op, "pos-ordem") == 0){

      if (root->len != 0){
        pos_ordem(root);
        printf("\n");
      }
      else{

        printf("vazia\n");
      }
    }
    else if (strcmp(op, "pre-ordem") == 0){

      if (root->len != 0){
        pre_ordem(root);
        printf("\n");
      }
      else{

        printf("vazia\n");
      }
    }
    else if (strcmp(op, "em-ordem") == 0){

      if (root->len != 0){
        em_ordem(root);
        printf("\n");
      }
      else{

        printf("vazia\n");
      }
    }

    else if (strcmp(op, "largura") == 0){

      if (root->len != 0){
        largura(root);

      }
      else{

        printf("vazia\n");
      }
    }

  } while(1);

  return 0;
}
