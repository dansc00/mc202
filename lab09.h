#ifndef LAB09H
#define LAB09H

typedef struct node{

  int data;
  int len;

  struct node *e; // apontador para o filho esquerdo
  struct node *d; // apontador para o filho direito

} tree;

int inserir(tree **root, int x);
int busca(tree *root, int n);
int pre_ordem(tree *node);
int pos_ordem(tree *node);
int em_ordem(tree *node);
int largura(tree *root);
int enfileirar(tree* fila, tree* node, int fila_len);

#endif
