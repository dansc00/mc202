#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab07.h"

int main(){

  int n; // valor passado para o elemento do vetor
  char com[13]; // comando requerido

  data.len = 0; // inicializa tamanho do vetor
  data.p_ocp = 0; // inicializa posições ocupadas do vetor

  // chamadas de funções

  do{

    scanf(" %s", com);

    if (strcmp("exit", com) == 0){
      break;
    }

    else if (strcmp("insert-first", com) == 0){

      scanf(" %d", &n);
      insert_first(&data, n);
      //printf("%d\n", data.vet[1]);
    }

    else if(strcmp("remove-first", com) == 0){

      remove_first(&data);

    }

    else if(strcmp("print-first", com) == 0){

      print_first(&data);
    }

    else if(strcmp("insert-last", com) == 0){

      scanf(" %d", &n);
      insert_last(&data, n);
    }

    else if(strcmp("remove-last", com) == 0){

      remove_last(&data);
    }

    else if(strcmp("print-last", com) == 0){

      print_last(&data);
    }

    else if(strcmp("is-empty", com) == 0){

      is_empty(&data);
    }
  
} while(1);


  return 0;
}
