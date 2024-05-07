#ifndef CALCULADORA_H
#define CALCULADORA_H

typedef struct Num{ // número gigante

    int alg; // algarismo

    struct Num *prox; // proximo elemento
}num;

num* cria_lista();
num* insere(num *l, char n);
void imprime(num *l);
num* espelha(num *l);
int verifica_maximo(num *l);
int verifica_numero_maior(num *l1, num * l2);
int verifica_digito_maior(num *l1, num *l2);
num* retira_zeros(num *l);
num* retira_zeros_exceto_ultimo(num *l);
void libera_lista(num *l);
void soma(num* n1, num* n2, num **res, int increm);
void subtracao(num *n1, num *n2, num **res, int decrem);
void multiplicacao(num *n1, int n2, num **res, int increm);
#endif