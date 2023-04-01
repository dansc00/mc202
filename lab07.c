#include <stdio.h>
#include <stdlib.h>

#include "lab07.h"

int insert_first(struct vet *data, int valor){

  int *new = (int*)malloc(sizeof(int)); // novo elemento

  if (data->len != 0){ // se o vetor possui pelo menos 1 posição preenchida

    if (data->p_ocp == data->len){ // se o número de posições ocupadas é igual ao tamanho do vetor

      int *copy = (int*)malloc((2*(data->len)) * sizeof(int)); // vetor cópia

      for (int i = 1; i < (data->p_ocp)+1; i++){ // copia o vetor, começando pelo elemento 1

				copy[i] = data->vet[i-1];

			}

			*new = valor; // atribui o valor ao novo elemento
			copy[0] = *new; // adiciona no inicio da copia
			data->vet = copy; // atualiza o vetor
      data->len = (data->len) * 2; // dobra o tamanho do vetor
			data->head = new; // cabeça recebe novo elemento


      ///free(copy); // libera vetor cópia

    }
		else{

			for (int k = 0; k < data->p_ocp; k++){ // empurra elementos para frente

				data->vet[k+1] = data->vet[k];
			}

      *new = valor; // atribui valor ao elemento novo
      data->vet = new; // insere no inicio
      data->head = new; // cabeça recebe novo elemento
    }
	}
  else{ // se o vetor está vazio

    *new = valor; // novo elemento recebe o valor dado
    data->vet = new; // adiciona primeiro elemento
		data->head = new; // cabeça se torna o novo elemento
   	(data->len)++;  // aumenta o tamanho em 1
  }

  (data->p_ocp)++; // aumenta o número de posições ocupadas após inserção


  return 0;
}

int remove_first(struct vet *data){
  if (data->p_ocp != 0){

    for (int i = 0; i < data->p_ocp; i++){

      data->vet[i] = data->vet[i+1];
    }
    data->vet[data->p_ocp] = 0;

    data->head = data->vet;
    (data->p_ocp)--;
    return 1;
  }
  else{

    return 0;
  }
}

int print_first(struct vet *data){

  if (data->p_ocp != 0){

    printf("%d\n", data->head);
    return 1;
  }
  else{

    return 0;
  }
}

int insert_last(struct vet *data, int valor){

  int *new = (int*)malloc(sizeof(int)); // novo elemento

  if (data->len != 0){ // se o vetor possui pelo menos 1 posição preenchida

    if (data->p_ocp == data->len){ // se o número de posições ocupadas é igual ao tamanho do vetor

      int *copy = (int*)malloc((2*(data->len)) * sizeof(int)); // vetor cópia

      for (int i = 0; i < data->p_ocp; i++){ // copia o vetor, começando pelo elemento 0

				copy[i] = data->vet[i];

			}

			*new = valor; // atribui o valor ao novo elemento
			copy[data->p_ocp] = *new; // adiciona no fim da copia
			data->vet = copy; // atualiza o vetor
      data->len = (data->len) * 2; // dobra o tamanho do vetor
			data->tail = new; // cauda recebe novo elemento


      ///free(copy); // libera vetor cópia

    }
		else{

      *new = valor; // atribui valor ao elemento novo
      data->vet[data->p_ocp] = *new; // insere no fim
      data->tail = new; // cauda recebe novo elemento
    }
	}
  else{ // se o vetor está vazio

    *new = valor; // novo elemento recebe o valor dado
    data->vet = new; // adiciona primeiro elemento
		data->tail = new; // cauda se torna o novo elemento
   	(data->len)++;  // aumenta o tamanho em 1
  }

  (data->p_ocp)++; // aumenta o número de posições ocupadas após inserção
}

int remove_last(struct vet *data){

  if (data->p_ocp != 0){

    data->vet[data->p_ocp] = 0;
    *data->tail = data->vet[data->p_ocp-1];

    (data->p_ocp)--;
    return 1;
  }
  else{

    return 0;
  }
}

int print_last(struct vet *data){

    if (data->p_ocp != 0){

      printf("%d\n", *data->tail);
      return 1;
    }
    else{

      return 0;
    }
}

int is_empty(struct vet *data){

  if (data->p_ocp == 0){

    printf("yes\n");
  }
  else{

    printf("no\n");
  }
}
