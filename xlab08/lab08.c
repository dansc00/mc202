#include <stdio.h>
#include <stdlib.h>

typedef struct NO{ // guarda nó da arvore binária

    int valor;

    struct NO *esq, *dir;

} NO;
//------------- fim da definição -----------------

// inicializa árvore
NO* inicializa_arvore(){

    return NULL;
}

// insere elemento na árvore
NO* insere_elemento(NO* aux, NO* raiz, NO* novo){

    if(raiz == NULL){

        raiz = novo;
    }
    else{

        if(novo->valor >= aux->valor){

            if(!aux->dir)
                aux->dir = novo;
            else
                raiz = insere_elemento(aux->dir, raiz, novo);
        }
        else{

            if(!aux->esq)
                aux->esq = novo;
            else
                raiz = insere_elemento(aux->esq, raiz, novo);
        }
    }

    return raiz;
}

// cria elemento e chama função de inserção
NO* cria_elemento_e_insere(NO* aux, NO* raiz, int chave){

    NO* novo = (NO*)malloc(sizeof(NO));

    novo->dir = NULL;
    novo->esq = NULL;
    novo->valor = chave;

    raiz = insere_elemento(aux, raiz, novo);

    return raiz;
}

// busca e retorna valor do sucessor do nó passado por parâmetro
int encontra_sucessor(NO* aux){

    int val_min = aux->dir->valor;
    NO* sucessor = aux->dir;

    while(sucessor){

        if(sucessor->valor < val_min)
            val_min = sucessor->valor;
        
        sucessor = sucessor->esq;
    }
    
    return val_min;
}

// remove elemento passado por parâmetro
NO* remove_elemento(NO* aux, NO* raiz, NO* removido, int chave, int sucessor){

    if(raiz == NULL){ // se a árvore é vazia

        return NULL;
    }
    else if(chave == raiz->valor){ // se o nó a ser removido é a raiz

        if(raiz->dir != NULL && raiz->esq == NULL){ // caso exista apenas filho a direita

            removido = raiz;
            raiz = raiz->dir;
            free(removido);
        }
        else if(raiz->dir == NULL && raiz->esq != NULL){ // caso exista apenas filho a esquerda

            removido = raiz;
            raiz = raiz->esq;
            free(removido);
        }
        else if(raiz->dir == NULL && raiz->esq == NULL){ // caso não haja filhos
            
            free(raiz);
            return NULL;
        }
        else{ // remove por sucessor

            sucessor = encontra_sucessor(raiz);
            raiz = remove_elemento(aux, raiz, removido, sucessor, 0);
            raiz->valor = sucessor;
        }
    }
    else{ 

        if(chave > aux->valor){  // caso a chave é maior, busca a direita

            if(aux->dir && aux->dir->valor == chave){

                if(aux->dir->esq == NULL && aux->dir->dir != NULL){

                    removido = aux->dir;
                    aux->dir = aux->dir->dir;
                    free(removido);
                }
                else if(aux->dir->esq != NULL && aux->dir->dir == NULL){

                    removido = aux->dir;
                    aux->dir = aux->dir->esq;
                    free(removido);
                }
                else if(aux->dir->esq == NULL && aux->dir->dir == NULL){

                    free(aux->dir);
                    aux->dir = NULL;
                }
                else{
                    
                    sucessor = encontra_sucessor(aux->dir);
                    raiz = remove_elemento(aux->dir, raiz, removido, sucessor, 0);
                    aux->dir->valor = sucessor;
                }
            }
            else{

                raiz = remove_elemento(aux->dir, raiz, removido, chave, 0);
            }
        }
        else if(chave < aux->valor){ // caso a chave é menor, busca a esquerda
            
            if(aux->esq && aux->esq->valor == chave){

                if(aux->esq->esq == NULL && aux->esq->dir != NULL){

                    removido = aux->esq;
                    aux->esq = aux->esq->dir;
                    free(removido);
                }
                else if(aux->esq->esq != NULL && aux->esq->dir == NULL){

                    removido = aux->esq;
                    aux->esq = aux->esq->esq;
                    free(removido);
                }
                else if(aux->esq->esq == NULL && aux->esq->dir == NULL){

                    free(aux->esq);
                    aux->esq = NULL;
                }
                else{

                    sucessor = encontra_sucessor(aux->esq);
                    raiz = remove_elemento(aux->esq, raiz, removido, sucessor, 0);
                    aux->esq->valor = sucessor;
                }
            }
            else{

                raiz = remove_elemento(aux->esq, raiz, removido, chave, 0);
            }
        }
    }

    return raiz;
}

// imprime na sequência pos ordem
void pos_ordem(NO* raiz){

    if(raiz == NULL)
        return;

    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%d ", raiz->valor);
}

// imprime na sequencia pre ordem
void pre_ordem(NO* raiz){

    if(raiz == NULL)
        return;

    printf("%d ", raiz->valor);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
}

// imprime na sequencia inordem
void inordem(NO* raiz){

    if(raiz == NULL)
        return;
    
    inordem(raiz->esq);
    printf("%d ", raiz->valor);
    inordem(raiz->dir);
}

// libera memória alocada na árvore
void libera_arvore(NO* raiz){

    if(raiz->esq){

        libera_arvore(raiz->esq);
        free(raiz->esq);
    }

    if(raiz->dir){

        libera_arvore(raiz->dir);
        free(raiz->dir);
    }
}
// --------------------- fim da implementação de funções -------------
int main(){

    int chave; // chave a ser inserida ou removida
    char opcao; // opção (inserção ou remoção)

    NO* raiz = inicializa_arvore(); 

    while(1){

        scanf(" %c", &opcao);

        if(opcao == 'F'){

            break;
        }
        else if(opcao == 'I'){

            scanf(" %d", &chave);
            raiz = cria_elemento_e_insere(raiz, raiz, chave);
        }
        else if(opcao == 'R'){

            scanf(" %d", &chave);
            raiz = remove_elemento(raiz, raiz, NULL, chave, 0);
        }
    }

    if(raiz){ // se a arvore n é vazia

        pre_ordem(raiz);
        printf("\n");
        
        inordem(raiz);
        printf("\n");

        pos_ordem(raiz);
        printf("\n");

        libera_arvore(raiz);
        free(raiz);
    }
    else{ // caso a árvore é vazia

        printf("ARVORE RESULTANTE VAZIA\n");
    }

    return 0;
}