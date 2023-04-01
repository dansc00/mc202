#ifndef LAB08H
#define LAB08H

typedef struct node{

  double data;
  int len; // tamanho da lista

  struct node *next; // proximo elemento
  struct node *prev; // elemento anterior

}list;

int insert(list **lista, int pos, double valor);
int reverter(list **lista, int pos1, int pos2);
int imprimir(list **lista);
list* indice(list *lista, int pos);


#endif
