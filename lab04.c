#include <stdio.h>
#include <string.h>

struct contato{

  char nome[51], end[101], data[11];
  int tel;

}

// Funcões-
//------------------------------------------------------------------

int rem(struct contato *r, int *ind){

  int num = 0; // numero de registros removidos
  char nrem[51]; // vetor nome que será removido e copia do vetor nome

  scanf(" %[^\n]", nrem);

  for (int i = 0; i < *ind; i++){ // percorre até o número de registros adicionadas até o momento

    if ((strcmp(nrem, r[i].nome)) == 0){

      num++; // +1 registro removido
      for (int j = i; j < *ind-1; j++){ // percorre os registros da posição a ser removida até o fim

        r[j]= r[j+1]; // aloca cada registro da posição j+1 na posição j

      }
      *ind = *ind-1;
      i = i-1; // i passa a iniciar da posição removida
    }
  }

  printf("Contatos de %s removidos: %d.\n", nrem, num);
  printf("\n");

  return 0;
}


//-----------------------------------------------------------------------
int bus(struct contato *r, int ind){

  int nbusc = 0; // numero de pessoas encontradas
  char busc[51]; // vetor nome buscado
  scanf("%s", busc);
  printf("Resultado da busca:\n");

  for(int i = 0; i < ind, i++){

    if ((strstr(r[i].nome, busc)) != NULL){ // se a palavra buscado corresponde ao nome no registro i

      nbusc++; // +1 registro encontrado
      printf("(%d) %s	%s	%d	%s\n", i+1, r[i].nome, r[i].end, r[i].tel, r[i].data);

    }
  }
  if (nbusc == 0){ // nenhum nome encontrado

    printf("Nenhum contato.\n");
  }
  printf("\n");
  return 0;
}
//----------------------------------------------------------------------

int imp(struct contato *r, int ind){

  printf("Listagem:\n");
  if (ind > 0){
    for (int i = 0; i < ind; i++){

      printf("(%d) %s	%s	%d	%s\n", i+1, r[i].nome, r[i].end, r[i].tel, r[i].data);
    }
    printf("\n");
  }
  else{
    printf("Nenhum Contato.\n");
  }
  return 0;
}

int main(){

  char op; // opção
  int ind = 0; // indice que acompanhará os contatos adicionados
  struct contato r[1000];

  while(1){

    scanf(" %c", &op); // opção de entrada
    if (op == 'i'){ // insere novo registro

      scanf(" %[^\n]", r[ind].nome);
      scanf(" %[^\n]", r[ind].end);
      scanf(" %d", &r[ind].tel);
      scanf(" %s", r[ind].data);

      printf("\nContato para %s inserido.\n", r[ind].nome);
      printf("\n");
      ind++; // novo registro
    }

    else if(op == 'r'){
      rem(r, &ind);
    }

    else if(op == 'b'){

      bus(r, ind);
    }

    else if(op == 'p'){

      imp(r, ind);
    }

    else if (op == 'f'){
      break;
    }
  }
  return 0;
}
