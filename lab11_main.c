#include <stdio.h>
#include <stdlib.h>

#include "lab11.h"

int main(){

  char op, string[251]; // operação de entrada
  hash* ha = (hash*)malloc(sizeof(hash)); // apontador para a tabela hashing

  ha->len_tab = 5013; // tamanho maximo da tabela
  ha->p_ocp = 0; // posições ocupadas inicia em 0
  ha->elem = (struct string**)malloc(ha->len_tab * sizeof(struct string*)); // aloca tabela

  while(1){

    scanf(" %c", &op);

    if (op == 'f'){ // terminar

      liberar(ha);
      break;
    }
    else if(op == 'i'){ // inserir

      scanf(" %s", string);
      inserir(&ha, string);
    }
    else if(op == 'b'){ // buscar

      scanf(" %s", string); // string buscada
      struct string *res; // resultado da busca, string
      res = busca(ha, string);

      if (res){ // se encontrou

        printf("%s encontrada, id %d\n", string, res->id);
      }
      else{

        printf("%s nao encontrada\n", string);
      }
    }
    else if(op == 'r'){

      scanf(" %s", string);
      remover(&ha, string);
    }
  }
  return 0;

}
