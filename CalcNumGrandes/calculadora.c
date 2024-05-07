#include <stdio.h>
#include <stdlib.h>
#define MAX_N 26 // maximo de algarismos do número. 1 x 10^24 + \0 = 26;

#include "calculadora.h"

int main(){

    int n; // número de entradas
    char op, *n1, *n2; // operação, lista q guarda numero 1, lista que guarda numero 2

    n1 = malloc(MAX_N * sizeof(char)); // aloca listas
    n2 = malloc(MAX_N * sizeof(char));

    scanf(" %d", &n);

    num *lista1, *lista2, *res, *res_mult, *res_aux, *lista2_aux;
    int pos; // marca a posição percorrida no número char e no resultado da multiplicação

    for(int i = 0; i < n; i++){ // percorre entradas
    
        lista1 = cria_lista(); // inicializa lista que guarda o número 1
        lista2 = cria_lista(); // inicializa lista que guarda o número 2 
        res = cria_lista(); // inicializa lista que guarda resultado 
        res_aux = cria_lista(); // inicializa lista auxiliar que guarda resultado parcial da mult.

        scanf(" %c", &op);
        scanf(" %s %s", n1, n2);
        pos = 0;

        while(*(n1+pos)){ // enquanto número 1 ñ terminou
            lista1 = insere(lista1, *(n1+pos)); // adiciona algarismo
            pos++;
        }

        pos = 0; // reseta posição

        while(*(n2+pos)){ // enquanto número 2 ñ terminou
            lista2 = insere(lista2, *(n2+pos)); // adiciona algarismo
            pos++;
        }

        pos = 0; // reseta posição

        switch(op){ // operações

            case '+': 

                soma(lista1, lista2, &res, 0); // soma
                imprime(res); // imprime resultado
                printf("\n");
            break;

            case '-':

                if(verifica_numero_maior(lista1, lista2) == 1) // verifica qual o maior número
                    subtracao(lista1, lista2, &res, 0); // subtrai 2 de 1
                else
                    subtracao(lista2, lista1, &res, 0); // subtrai 1 de 2

                res = retira_zeros(res);

                if(res)
                    res = espelha(res);

                if(res){ // se existe resultado
                   imprime(res);
                }
                else{ // se nulo
                    printf("%d", 0);   
                }
                printf("\n");
            break;

            case '*':

                if(lista1->alg != 0 || lista1->prox){
                    lista2_aux = lista2;
                    while(lista2_aux){ // percorre lista2

                        res_mult = cria_lista(); // cria lista que recebe o resultado da multiplicação;

                        for(int j = 0; j < pos; j++) // adiciona zeros para cada parte da multiplicação
                            res_mult = insere(res_mult, '0');
                
                        multiplicacao(lista1, lista2_aux->alg, &res_mult, 0); // multiplicação

                        if(verifica_maximo(res_mult) != 0)
                            res_mult = retira_zeros(res_mult);
                        else
                            res_mult = retira_zeros_exceto_ultimo(res_mult);
                        
                        
                        if(res_aux && pos != 0){ // se existe res_aux e não é a primeira multiplicação
                            
                            res_aux = espelha(res_aux); // inverte
                            soma(res_aux, res_mult, &res, 0); // soma com o resultado da multiplicação
                            libera_lista(res_aux); // libera 
                            res_aux = cria_lista();
                        }
                        else if(res){

                            res = espelha(res);
                            soma(res, res_mult, &res_aux, 0);
                            libera_lista(res);
                            res = cria_lista();
                        }

                    if(pos == 0){ // se for a primeira multiplicação

                            soma(res_aux, res_mult, &res_aux, 0); 
                        }               

                        pos++;
                        lista2_aux = lista2_aux->prox;
                        libera_lista(res_mult);
                    }
                }
                
                if(res){ // se o resultado final está em res

                    imprime(res);
                    
                    libera_lista(res);
                    res = cria_lista();
                }
                else if(res_aux){ // se o resultado final está em res_aux

                    imprime(res_aux);
                    
                    libera_lista(res_aux);
                    res_aux = cria_lista();
                }
                else{
                    printf("%d", 0);
                }

                printf("\n");
            break;
        }

        if(res)
            libera_lista(res); // libera resultado

        libera_lista(lista1); // libera numero 1
        libera_lista(lista2); // libera numero 2
    }

    free(n1); // libera vetor de caracter 1
    free(n2); // libera vetor de caracter 2

    return 0;
}