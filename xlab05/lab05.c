#include <stdio.h>
#include <stdlib.h>

// armazena os dados de cada linha e cada coluna da matriz esparsa
typedef struct Elemento{

    int valor;
    int linha;
    int coluna;

    struct Elemento *prox_linha;
    struct Elemento *prox_coluna;

}elemento;
//------------ fim da definição -----------------

// aloca super nó da matriz
elemento* inicializa_super_no(int n){

    elemento* sup_no = (elemento*)malloc(sizeof(elemento));

    sup_no->valor = 0;
    sup_no->linha = n;
    sup_no->coluna = n;
    sup_no->prox_linha = sup_no;
    sup_no->prox_coluna = sup_no;

    return sup_no;
}

// aloca cabeças de linha da matriz
elemento* cria_cabeca_linha(elemento *matriz, int n){

    elemento* aux = matriz;

    for(int i = 0; i < n; i++){

        elemento* cabeca_linha = (elemento*)malloc(sizeof(elemento));

        cabeca_linha->valor = 0;
        cabeca_linha->linha = i+1;
        cabeca_linha->coluna = -1;
        cabeca_linha->prox_linha = cabeca_linha;
        cabeca_linha->prox_coluna = cabeca_linha;

        aux->prox_coluna = cabeca_linha;
        aux = cabeca_linha;
    }

    aux->prox_coluna = matriz;

    return matriz;
}

// aloca cabeças de coluna da matriz
elemento* cria_cabeca_coluna(elemento *matriz, int n){

    elemento* aux = matriz;

    for(int i = 0; i < n; i++){

        elemento* cabeca_coluna = (elemento*)malloc(sizeof(elemento));

        cabeca_coluna->valor = 0;
        cabeca_coluna->linha = -1;
        cabeca_coluna->coluna = i+1;
        cabeca_coluna->prox_linha = cabeca_coluna;
        cabeca_coluna->prox_coluna = cabeca_coluna;

        aux->prox_linha = cabeca_coluna;
        aux = cabeca_coluna;
    }

    aux->prox_linha = matriz;

    return matriz;
}

// insere elemento na linha desejada
elemento* insere_na_linha(elemento *matriz, elemento *novo, int linha){

    elemento *aux_linha; // percorre na linha
    elemento *aux_coluna; // percorre na coluna

    aux_coluna = matriz;
    for(int i = 0; i < linha; i++){ 

        aux_coluna = aux_coluna->prox_coluna;
    }
    if(aux_coluna->prox_linha == aux_coluna){ // se a linha está vazia

        novo->prox_linha = aux_coluna;
        aux_coluna->prox_linha = novo;
        novo->prox_coluna = novo;
    }
    else{

        aux_linha = aux_coluna;

        // percorre para inserir na coluna correta
        while(novo->coluna > aux_linha->prox_linha->coluna && aux_linha->prox_linha != aux_coluna)
            aux_linha = aux_linha->prox_linha;
        

        if(aux_linha->prox_linha == aux_coluna){ // se for o ultimo elemento da linha

            novo->prox_linha = aux_coluna;
            aux_linha->prox_linha = novo;
            novo->prox_coluna = novo;
        }
        else{

            novo->prox_linha = aux_linha->prox_linha;
            aux_linha->prox_linha = novo;
            novo->prox_coluna = novo;
        }
    }

    return matriz;
}

// insere elemento na coluna desejada
elemento* insere_na_coluna(elemento *matriz, elemento *novo, int coluna){

    elemento *aux_linha; // percorre na linha
    elemento *aux_coluna; // pecorre na coluna

    aux_linha = matriz;
    for(int j = 0; j < coluna; j++){

        aux_linha = aux_linha->prox_linha;
    }
    if(aux_linha->prox_coluna == aux_linha){ // se a coluna está vazia

        novo->prox_coluna = aux_linha;
        aux_linha->prox_coluna = novo;
    }
    else{

        aux_coluna = aux_linha;

        // percorre linhas até a posição correta
        while(novo->linha > aux_coluna->prox_coluna->linha && aux_coluna->prox_coluna != aux_linha)
            aux_coluna = aux_coluna->prox_coluna;
        

        if(aux_coluna->prox_coluna == aux_linha){ // se é o ultimo elemento na coluna

            novo->prox_coluna = aux_linha;
            aux_coluna->prox_coluna = novo;
        }
        else{

            novo->prox_coluna = aux_coluna->prox_coluna;
            aux_coluna->prox_coluna = novo;
        }
    }

    return matriz;
}
// aloca elemento e insere na coluna e linha passadas por parâmetro
elemento* insere_elemento(elemento *matriz, int linha, int coluna, int valor){

    elemento *novo = (elemento*)malloc(sizeof(elemento));
    novo->valor = valor;
    novo->linha = linha;
    novo->coluna = coluna;

    matriz = insere_na_linha(matriz, novo, linha);
    matriz = insere_na_coluna(matriz, novo, coluna);

    return matriz;
}

// soma duas matrizes e retorna a matriz resultante
elemento* soma_matrizes(elemento* matriz1, elemento* matriz2, elemento* matriz_res, int n){

    elemento* aux_coluna1 = matriz1; // percorre nas colunas da matriz1
    elemento* aux_linha1; // percorre nas linhas da matriz2

    elemento* aux_coluna2 = matriz2; // percorre nas colunas da matriz2
    elemento* aux_linha2; // percorre nas linhas da matriz2

    for(int i = 0; i < n; i++){

        aux_coluna1 = aux_coluna1->prox_coluna;
        aux_coluna2 = aux_coluna2->prox_coluna;
        aux_linha1 = aux_coluna1;
        aux_linha2 = aux_coluna2;

        for(int j = 0; j < n; j++){
            
            // se a linha é vazia
            if(aux_linha1->prox_linha->coluna == -1 && aux_linha2->prox_linha->coluna == -1)
                break;

            if(aux_linha1->prox_linha->coluna == j+1) // se o elemento atual está na coluna atual
                aux_linha1 = aux_linha1->prox_linha;
                
            if(aux_linha2->prox_linha->coluna == j+1)
                aux_linha2 = aux_linha2->prox_linha;
                            
            // se existem elementos na coluna atual nas 2 matrizes
            if(aux_linha1->coluna == j+1 && aux_linha2->coluna == j+1){ 

                matriz_res = insere_elemento(matriz_res, i+1, j+1, (aux_linha1->valor + aux_linha2->valor));
            }
            else{
                // se existe o elemento apenas na primeira matriz
                if(aux_linha1->coluna == j+1){

                    matriz_res = insere_elemento(matriz_res, i+1, j+1, aux_linha1->valor);
                }
                // se existe o elemento apenas na segunda matriz
                else if(aux_linha2->coluna == j+1){

                    matriz_res = insere_elemento(matriz_res, i+1, j+1, aux_linha2->valor);
                }
            }
        }
    }

    return matriz_res;
}

// imprime matriz resultante da soma
void imprime_saida(elemento* matriz_res, int n){

    elemento* aux_coluna = matriz_res;
    elemento* aux_linha;

    for(int i = 0; i < n; i++){
        
        aux_coluna = aux_coluna->prox_coluna;
        aux_linha = aux_coluna;

        for(int j = 0; j < n; j++){

            if(aux_linha->prox_linha->coluna == j+1)
                aux_linha = aux_linha->prox_linha;

            if(aux_linha->coluna == j+1){

                printf("%d ", aux_linha->valor);
            }
            else{

                printf("%d ", 0);
            }
        }
        printf("\n");
    }
}

// libera memória alocada na matriz
void libera_matriz(elemento *matriz, int n){

    elemento* aux_coluna = matriz;
    elemento* aux_linha;
    elemento* liberado;

    for(int i = 0; i < n; i++){

        aux_coluna = aux_coluna->prox_coluna;

        if(aux_coluna->prox_linha->coluna == -1) // se a linha é vazia
            continue;

        aux_linha = aux_coluna->prox_linha;

        do{

            liberado = aux_linha;
            aux_linha = aux_linha->prox_linha;
            free(liberado);

        }while(aux_linha->coluna != -1);
    }
}

// libera memória alocada nas cabeças de nó
void libera_cabecas(elemento* matriz, int n){

    elemento* linha = matriz->prox_coluna; // percorre linhas
    elemento* linha_liberada; // armazena linha a ser liberada

    elemento* coluna = matriz->prox_linha; // percorre colunas
    elemento* coluna_liberada; // armazena coluna a ser liberada

    for(int i = 0; i < n; i++){

        linha_liberada = linha;
        linha = linha->prox_coluna;
        free(linha_liberada);
    }

    for(int j = 0; j < n; j++){

        coluna_liberada = coluna;
        coluna = coluna->prox_linha;
        free(coluna_liberada);
    }
}
//----------- fim da implementação de funções ------------------------------------

int main(){

    int n; // ordem das matrizes
    scanf(" %d", &n);

    int linha; // linha a ser lida
    int coluna; // coluna a ser lida
    int valor; // valor a ser lido

    elemento* matriz1 = inicializa_super_no(n); // inicializa super nó da matriz1
    elemento *matriz2 = inicializa_super_no(n); // inicializa super nó da matriz2
    elemento* matriz_res = inicializa_super_no(n); // inicializa super nó da matriz resultado

    matriz1 = cria_cabeca_linha(matriz1, n); // cria cabeças de nós da matriz1
    matriz1 = cria_cabeca_coluna(matriz1, n);

    matriz2 = cria_cabeca_linha(matriz2, n); // cria cabeças de nós da matriz2
    matriz2 = cria_cabeca_coluna(matriz2, n);

    matriz_res = cria_cabeca_linha(matriz_res, n); // cria cabeças de nós da matriz resultado
    matriz_res = cria_cabeca_coluna(matriz_res, n);

    while(1){ // leitura da matriz1

        scanf(" %d %d %d", &linha, &coluna, &valor);

        if(linha == -1 && coluna == -1 && valor == -1)
            break;

        matriz1 = insere_elemento(matriz1, linha, coluna, valor);
    }

    while(1){ // leitura da matriz2

        scanf(" %d %d %d", &linha, &coluna, &valor);

        if(linha == -1 && coluna == -1 && valor == -1)
            break;

        matriz2 = insere_elemento(matriz2, linha, coluna, valor);
    }

    matriz_res = soma_matrizes(matriz1, matriz2, matriz_res, n); // soma matriz1 com matriz2

    imprime_saida(matriz_res, n); // imprime matriz resultante

    //libera memória
    libera_matriz(matriz1, n);
    libera_matriz(matriz2, n);
    libera_matriz(matriz_res, n);

    libera_cabecas(matriz1, n);
    libera_cabecas(matriz2, n);
    libera_cabecas(matriz_res, n);

    free(matriz1);
    free(matriz2);
    free(matriz_res);

    return 0;
}