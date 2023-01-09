#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{ // lista que armazena a entrada inordem e pre ordem
     
    char dado;

    struct Lista* prox_lista;

} lista;

typedef struct Arvore{

    char dado;

    struct Arvore* esq;
    struct Arvore* dir;

} arvore;
//-------------- fim da definição -------------------

// inicializa lista
lista* cria_lista(){
    return NULL;
}

// insere na lista
lista* insere_lista(lista* l, char entrada){

    lista *aux = l;

    lista* novo = (lista*)malloc(sizeof(lista));
    novo->dado = entrada;
    novo->prox_lista = NULL;

    if(l){

        while(aux->prox_lista)
            aux = aux->prox_lista;

        aux->prox_lista = novo;
    }
    else{

        l = novo;
    }

    return l;
}

// inicializa arvore
arvore* cria_arvore(){
    return NULL;
}

// verifica posição do novo em relação ao no na sequencia inordem. retorna 1 caso esquerda e 0 caso direita
int verifica_posicao_filho(lista* inordem, arvore* no, arvore* novo){

    lista* aux = inordem;

    while(1){

        if(aux->dado == novo->dado)
            return 1;

        if(aux->dado == no->dado)
            break;

        aux = aux->prox_lista;
    }

    return 0;
}

// insere recursivamente no na arvore
arvore* insere_arvore(arvore* no, arvore* raiz, lista* inordem, arvore* novo){

    if(!raiz){ // se a arvore é vazia

        raiz = novo;
    }
    else{

        if(verifica_posicao_filho(inordem, no, novo)){ // se o filho precisa ser inserido a esquerda

            if(!no->esq){ // se n existe filho a esquerda insere a esquerda

                no->esq = novo;
            }
            else{ // se existe filho a esquerda verifica novamente a posição a partir desse filho

                raiz = insere_arvore(no->esq, raiz, inordem, novo);
            }
        }
        else{ // se o filho precisa ser inserido a direita

            if(!no->dir){ // se n existe filho a direita insere a direita

                no->dir = novo;
            }
            else{ // se existe filho a direita verifica novamente a posição a partir desse filho

                raiz = insere_arvore(no->dir, raiz, inordem, novo);
            }
        }
    }

    return raiz;       
}

// cria elemento novo e chama função de inserção
arvore* cria_elemento_arvore(arvore* no, arvore* raiz, lista* inordem, char dado){

    arvore* novo = (arvore*)malloc(sizeof(arvore));
    novo->dado = dado;
    novo->esq = NULL;
    novo->dir = NULL;

    raiz = insere_arvore(no, raiz, inordem, novo);

    return raiz;
}

// imprime sequencia pos ordem
void pos_ordem(arvore* no){

    if(no->esq){

        pos_ordem(no->esq);
        printf("%c ", no->esq->dado);
    }

    if(no->dir){

        pos_ordem(no->dir);
        printf("%c ", no->dir->dado);
    }
}

// libera memoria alocada na arvore
void libera_arvore(arvore* no){

    if(no->esq){

        libera_arvore(no->esq);
        free(no->esq);
    }

    if(no->dir){

        libera_arvore(no->dir);
        free(no->dir);
    }
}

// libera memoria alocada na lista
void libera_lista(lista* l){

    if(l->prox_lista){

        libera_lista(l->prox_lista);
    }

    free(l);
}

// ---------------  fim da implementação de funções -----------------
int main(){

    int n; // numero de elementos na arvore
    scanf(" %d", &n);

    lista* inordem = cria_lista();
    lista* pre_ordem = cria_lista();
    lista* aux; // percorre lista pre ordem

    arvore* raiz = cria_arvore();

    char entrada; // armazena entrada

    for(int i = 0; i < n; i++){ // cria lista com sequencia pre ordem

        scanf(" %c", &entrada);

        pre_ordem = insere_lista(pre_ordem, entrada);
    }

    for(int j = 0; j < n; j++){ // cria lista com sequencia inordem

        scanf(" %c", &entrada);

        inordem = insere_lista(inordem, entrada);
    }

    aux = pre_ordem;

    while(aux){ // constrói árvore

        raiz = cria_elemento_arvore(raiz, raiz, inordem, aux->dado);
        aux = aux->prox_lista;
    }

    pos_ordem(raiz); // printa sequencia pos ordem
    printf("%c \n", raiz->dado); // printa raiz

    // libera memória alocada
    libera_arvore(raiz);
    libera_lista(pre_ordem);
    libera_lista(inordem);
    free(raiz);

    return 0;
}