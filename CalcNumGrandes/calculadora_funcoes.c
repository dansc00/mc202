#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculadora.h"

num* cria_lista(){ // inicializa lista
    return NULL;
}
//---------------------------------------------------------------------------------
num* insere(num *l, char n){ // insere elemento na lista

    num *novo;
    novo = malloc(sizeof(num));
    novo->alg = n - '0'; // converte char para int
    novo->prox = l;

    return novo;
}
//--------------------------------------------------------------------------------
void imprime(num *l){ // imprime os nós da lista de trás pra frente

    while(l){
        printf("%d", l->alg);
        l = l->prox;      
    }
}
//---------------------------------------------------------------------------------
num* espelha(num* l){
// copia lista de trás pra frente
    num* esp;
    esp = cria_lista();
    num *aux = l;
    while(aux){

        esp = insere(esp, aux->alg + '0');
        aux = aux->prox;
    }

    libera_lista(l);
    return esp;
}
//---------------------------------------------------------------------------
num* copia_lista(num *l){
// copia lista
    num *cop = cria_lista();
    while(l){

        cop = insere(cop, l->alg + '0');
        l = l->prox;
    }

    return cop;
}
//-----------------------------------------------------------------------------
int verifica_maximo(num *l){
// devolve máximo em uma lista
    int max = l->alg;

    while(l->prox){
        l = l->prox;

        if(l->alg > max)
            max = l->alg;
    }

    return max;
}
//-------------------------------------------------------------------------------------------------
int verifica_numero_maior(num *l1, num *l2){
// verifica qual o maior número passado
    num *aux1, *aux2;
    aux1 = l1;
    aux2 = l2;

    while(aux1->prox && aux2->prox){
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }

    if(aux1->prox)
        return 1;
    else if(aux2->prox)
        return 0;
    else if(!aux1->prox && !aux2->prox){
        return verifica_digito_maior(l1, l2);
    }

    return 1;
}
//-------------------------------------------------------------------------------------------------
int verifica_digito_maior(num *l1, num *l2){
// caso empate em algarismos na verificação de maior número, verifica digito por digito até encontrar maior
    num *cop1 = copia_lista(l1);
    num *cop2 = copia_lista(l2);

    num *aux1, *aux2;

    aux1 = cop1;
    aux2 = cop2;
     
    while(aux1 != NULL && aux2 != NULL){

        if(aux1->alg > aux2->alg){
            libera_lista(cop1);
            libera_lista(cop2);
            return 1;
        }
        else if(aux2->alg > aux1->alg){
            libera_lista(cop1);
            libera_lista(cop2);
            return 0;
        }
        
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }

    return 1;
}  
//----------------------------------------------------------------------------------------------------
void libera_lista(num *l){ // libera lista ligada passada por parâmetro

    if(l){
        libera_lista(l->prox);
        free(l);   
    }
}
//----------------------------------------------------------------------------------
num* retira_zeros(num *l){
// elimina zeros a esquerda do resultado
    num *new = cria_lista();
    num *aux = l;
    while(aux && aux->alg == 0){
        
        aux = aux->prox;
    }

    if(aux){
        while(aux){

            new = insere(new, aux->alg + '0');
            aux = aux->prox;
        }
    }
    libera_lista(l);
    return new;
}
//----------------------------------------------------------------------------
num* retira_zeros_exceto_ultimo(num *l){
// elimina zeros exceto o último, no caso para resultado nulo
    num *aux = l;
    num *new = cria_lista();

    while(aux->prox){
        aux = aux->prox;
    }

    new = insere(new, aux->alg + '0');
    libera_lista(l);
    return new;
}
//--------------------------------------------------------------------------
void soma(num* n1, num* n2, num **res, int increm){ // soma os números n1 e n2 e devolve o resultado
// increm é o incremento que será 1 caso o resultado for acima de 9 e 0 caso contrário

    if(n1 != NULL && n2 != NULL){ // se os dois números ainda não chegaram ao fim

        if((n1->alg + n2->alg + increm) >= 0 && (n1->alg + n2->alg + increm) <= 9){ // caso a soma esteja entre 0 e 9
            *res = insere(*res, (n1->alg + n2->alg + increm)+'0'); // adiciona resultado
            soma(n1->prox, n2->prox, res, 0); // proxima posição
        }
        else if((n1->alg + n2->alg + increm >= 10)){ // caso a soma é maior que 9
            *res = insere(*res, (n1->alg + n2->alg + increm - 10)+'0');
            soma(n1->prox, n2->prox, res, 1);
        }
    }
    else if(n1 == NULL && n2 != NULL){ // se o primeiro número chegou ao fim

        
        while(n2){ // percorre até terminar o número 2
            if(n2->alg + increm <= 9){
                *res = insere(*res, (n2->alg + increm) + '0');
                increm = 0;
            }
            else{
                *res = insere(*res, (n2->alg + increm - 10) + '0');
            }
            n2 = n2->prox;
        }
        if(increm > 0)
            *res = insere(*res, increm + '0');
    }
    else if(n1 != NULL && n2 == NULL){ // se o segundo número chegou ao fim

        
        while(n1){ // percorre até terminar n1
            if(n1->alg + increm <= 9){
                *res = insere(*res, (n1->alg + increm) + '0');
                increm = 0;
            }
            else{
                *res = insere(*res, (n1->alg + increm - 10) + '0');
            }
            n1 = n1->prox;
        }
        if(increm > 0)
            *res = insere(*res, increm + '0');
    }
    else{ // se os dois acabaram juntos
        if(increm > 0)
            *res = insere(*res, increm + '0');
    }
}
//---------------------------------------------------------------------------------------------
void subtracao(num *n1, num *n2, num **res, int decrem){ // subtrai numero 2 de 1
// decrem é o valor que será retirado caso o número precise emprestar a outro
    if(n1 != NULL && n2 != NULL){ // se os dois algarismos existem

        if(n1->alg - decrem - n2->alg >= 0 && n1->prox){ // se a subtração resulta positivo

            *res = insere(*res, (n1->alg - decrem - n2->alg) + '0'); // insere número
            subtracao(n1->prox, n2->prox, res, 0); // sem decremento
        }
        else if(n1->alg - decrem - n2->alg > 0 && !n1->prox){

            *res = insere(*res, (n1->alg - decrem - n2->alg) + '0'); // insere número
            subtracao(n1->prox, n2->prox, res, 0); // sem decremento
        }
        else if(n1->alg - decrem - n2->alg == 0 && !n1->prox){

            subtracao(n1->prox, n2->prox, res, 0);
        }
        else if(n1->alg - decrem - n2->alg < 0){
            
            if(n1->prox){
                *res = insere(*res, ((n1->alg + 10 - decrem) - n2->alg) + '0');
                subtracao(n1->prox, n2->prox, res, 1); // com decremento
            }
            else{
                *res = insere(*res, ((n1->alg - n2->alg) * -1) + '0');
                subtracao(n1->prox, n2->prox, res, 0);
            }
            
        }
    }
    else if(n1 == NULL && n2 != NULL){ // se numero 1 acabou e 2 ainda existe
        
        while(n2){ // insere os números restantes em 2
            *res = insere(*res, n2->alg + '0');
            n2 = n2->prox;
        }
    }
    else if(n1 != NULL && n2 == NULL){ // se numero 1 ainda existe e 2 acabou

        while(n1){ // insere os números em 1 decrementando o primeiro caso haja decremento
            *res = insere(*res, (n1->alg - decrem) + '0');
            decrem = 0;
            n1 = n1->prox;
        }
    }
    
}
//-----------------------------------------------------------------------------------------
void multiplicacao(num* n1, int n2, num **res, int increm){

    if(n1){ // se o número 1 existe

        if(n2 * n1->alg + increm < 10){ // se a multiplicação é menor que 10

            *res = insere(*res, (n2 * n1->alg + increm) + '0'); // insere
            multiplicacao(n1->prox, n2, res, 0);
        }
        else{

            *res = insere(*res, ((n2 * n1->alg + increm) % 10) + '0'); // insere unidade
            multiplicacao(n1->prox, n2, res, (int)((n2 * n1->alg + increm) / 10)); // passa dezena como incremento
        }
    }       
    else{ // se o número chegou ao fim

        if(increm > 0)
            *res = insere(*res, increm + '0');
    }
}