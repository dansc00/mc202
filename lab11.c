#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab11.h"

// funções de hashing

int hash1_divisao(int len_tab, char *str){

  unsigned long chave = conversor(str);

  return chave % len_tab;

}

int hash2_multiplicacao(int len_tab, char *str){

  unsigned long chave = conversor(str);

  float cnt = 0.6180339887;
  float val = chave * cnt;

  val = val - (int)val;

  return (int)(val * len_tab);
}

unsigned long conversor(unsigned char *str){

  unsigned long v = 5381;
  int len_string = strlen(str);

  for (int i = 0; i < len_string; i++){

    v = v * 32 + v + (int)str[i];
  }
  return v;
}
//-------------------------------------------------------------------------------------------------------------------

string* busca(hash *ha, char *str){

  int pos;
  int n_colisoes = 0;
  int n_testes = 0; // numero de testes feitos

  do{

    pos = (hash1_divisao(ha->len_tab, str)  +  n_colisoes  *  hash2_multiplicacao(ha->len_tab, str))  %  ha->len_tab; // duplo hash
    n_colisoes++; // incrementa numero de colisoes
    n_testes++; // incrementa teste

    if (ha->elem[pos] != NULL && strcmp(ha->elem[pos]->str, "#") != 0){ // se o elemento na posição não é nulo e não é uma cadeia removida

      if (strcmp(ha->elem[pos]->str, str) == 0){ // se a string é a procurada
        return ha->elem[pos];
      }
    }

  } while(ha->elem[pos] != NULL && strcmp(ha->elem[pos]->str, "#") != 0 && n_testes < ha->len_tab); // enquanto o valor da posição não for NULL, não ser uma cadeia removida e não forem testadas todas posições possiveis da tabela

  return NULL;
}

//--------------------------------------------------------------------------------------------------------------------
int inserir(hash **ha, char *str){

  if ((*ha)->p_ocp < (*ha)->len_tab){ // se a tabela não está cheia ainda

    string *n_cadeia = (string*)malloc(sizeof(string)); // nova cadeia

    strncpy(n_cadeia->str, str, (strlen(str))+1); // copia cadeia

    if (busca(*ha, n_cadeia->str) == NULL){ // se a cadeia buscada não está na tabela

      n_cadeia->id = (*ha)->p_ocp; // identificador da cadeia é atualizado

      int pos; // posição a ser inserida a nova cadeia
      int n_colisoes = 0; // contador do numero de colisoes

      do{

        pos = (hash1_divisao((*ha)->len_tab, n_cadeia->str)  +  n_colisoes  *  hash2_multiplicacao((*ha)->len_tab, n_cadeia->str))  %  (*ha)->len_tab; // duplo hash
        n_colisoes++; // incrementa numero de colisoes

      } while((*ha)->elem[pos] != NULL); // enquanto houver colisão

      (*ha)->elem[pos] = n_cadeia;

      (*ha)->p_ocp++; // incrementa posições ocupadas

      return 1;
    }
  }

  return 0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int remover(hash **ha, char *str){

  string *r = busca(*ha, str);

  if (r){

    strcpy(r->str, "#"); // atribui # para representar cadeias removidas

    return 1;
  }

  return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int liberar(hash *ha){

  if (ha){ // se existe a tabela

    for (int i = 0; i < ha->len_tab; i++){ // percorre todas posições

      if(ha->elem[i]){ // se existe cadeia alocada

        free(ha->elem[i]); // libera cadeia
      }
    }

    free(ha->elem); // libera vetor de apontadores para string
    free(ha); // libera tabela
  }

  return 0;
}
