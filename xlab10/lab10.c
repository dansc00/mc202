#include <stdio.h>
#include <stdlib.h>

typedef struct fp{

    int *valor; // vetor q armazena elementos do heap
    int n; // numero de elementos no heap
    int tam; // tamanho maximo do heap

} fp;

#define MAX_HEAP 100 // tamanho máximo do heap

// ------------------- fim da definição--------------------

// cria heap
fp* cria_heap(int tam){

    fp* heap = (fp*)malloc(sizeof(fp));
    heap->n = 0;
    heap->tam = tam;
    heap->valor = (int*)malloc(heap->tam * sizeof(int));

    return heap;
}

// insere elemento no heap e reorganiza subindo no heap
void insere(fp* heap, int valor){

    int i, pai; // marca posição do elemento no heap e do seu pai
    int aux; // auxiliar para troca

    heap->valor[heap->n] = valor;
    heap->n++;

    i = heap->n - 1;

    while(i > 0){ // sobe no heap

        pai = ((i-1)/2);

        if(heap->valor[pai] < heap->valor[i]){ // se o valor do pai é menor q o filho, troca de posição

            aux = heap->valor[i];
            heap->valor[i] = heap->valor[pai];
            heap->valor[pai] = aux;
        }

        i = pai;
    }
}

// extrai maior valor do heap e reorganiza descendo no heap
int extrai_maximo(fp* heap){

    int aux; // auxiliar para troca

    // troca primeiro elemento com último
    aux = heap->valor[heap->n - 1];
    heap->valor[heap->n - 1] = heap->valor[0];
    heap->valor[0] = aux;

    heap->n--; // decrementa o heap

    int i = 0; // posição em análise
    int dir, esq; // marca posições dos filhos a esquerda e direita de i
    int max_filho; // maior filho de i

    do{

        esq = 2*i+1;
        dir = 2*i+2;

        max_filho = esq;
        
        if(dir < heap->n && heap->valor[esq] < heap->valor[dir]) // se o filho a direita é maior
            max_filho = dir;
        
        if(max_filho < heap->n && heap->valor[max_filho] > heap->valor[i]){ // se o filho é maior q o pai

            aux = heap->valor[i];
            heap->valor[i] = heap->valor[max_filho];
            heap->valor[max_filho] = aux;
        }

        i = max_filho;

    } while(i < heap->n-1);

    return 0;
}

// printa heap completo
void escreve(fp* heap){

    if(heap->n > 0){

        for(int i = 0; i < heap->n; i++)

            printf("%d ", heap->valor[i]);
    }
    else{

        printf("VAZIO");
    }

    printf("\n");
}
// -------- fim da implementação ---------------------------

int main(){

    int valor; // valor a ser inserido no heap
    char opr; // operação desejada

    fp* heap = cria_heap(MAX_HEAP); // heap de máximo

    while(1){

        scanf(" %c", &opr);

        if(opr == 'I'){

            scanf(" %d", &valor);
            insere(heap, valor);
            escreve(heap);
        }
        else if(opr == 'M'){

            extrai_maximo(heap);
            escreve(heap);
        }
        else if(opr == 'F'){

            break;
        }
    }

    free(heap->valor); // libera vetor 
    free(heap); // libera heap

    return 0;
}