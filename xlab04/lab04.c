#include <stdio.h>
#include <stdlib.h>

// armazena dados de um produto
typedef struct Produto{

    int id_prod; // id do produto
    int n_subprods; // numero de subprodutos
    int *ids_subprods; // ids dos subprodutos
    float preco_base; // preço base caso o produto seja matéria prima
    float imposto; // percentual de imposto
    float preco_final; // marca preço final de cada produto

}produto;

// inicializa vetor de produtos
produto* cria_vetor(int n){

    produto *vetor = (produto*)malloc(n * sizeof(produto));

    return vetor;
}

// insere no vetor de produtos
void insere(produto *vetor, int pos){

    produto novo; // novo produto
    scanf(" %d %d", &(novo.id_prod), &(novo.n_subprods)); // lê id e numero de subprodutos

    if(novo.n_subprods != 0){ // se há subprodutos

        novo.ids_subprods = (int*)malloc(novo.n_subprods * sizeof(int)); // aloca vetor de subprodutos

        for(int i = 0; i < novo.n_subprods; i++)
            scanf(" %d", &(novo.ids_subprods[i])); // adiciona ids dos subprodutos
        
    }
    else{ // se é matéria prima

        scanf(" %f", &(novo.preco_base)); // lê preço base
    }

    scanf(" %f", &(novo.imposto)); // lê imposto
    novo.preco_final = 0;

    vetor[pos] = novo; // armazena no vetor
}
// calcula preço final do produto alvo
void calcula_preco(produto *alvo, produto* vetor, produto aux, float *preco_total, float* preco_atual, int n, produto atual){

    if(alvo->n_subprods != 0){ // caso haja subprodutos

        atual = *alvo; // marca produto atual
        for(int i = 0; i < alvo->n_subprods; i++){
            for(int j = 0; j < n; j++){

                if(alvo->ids_subprods[i] == vetor[j].id_prod){

                    if(vetor[j].preco_final == 0) // se o preço ainda n foi marcado
                        calcula_preco(&vetor[j], vetor, aux, preco_total, preco_atual, n, atual);
                    else
                        *preco_atual += vetor[j].preco_final; // incrementa preco do subproduto com subprodutos

                    break;
                }
            }  
        }

        if(aux.id_prod != alvo->id_prod && alvo->preco_final == 0){ // caso n seja o produto alvo

            alvo->preco_final = (*preco_atual * (1.0 + (alvo->imposto/100)));
            *preco_total += alvo->preco_final;
        }
        else{

            *preco_total = (*preco_total * (1.0 + (alvo->imposto/100)));
        }

        *preco_atual = 0;
    }
    else{

        if(atual.id_prod != aux.id_prod){ // caso n seja um subproduto do produto atual

            alvo->preco_final = (alvo->preco_base*(1.0 + (alvo->imposto/100)));
            *preco_atual += alvo->preco_final;
        }
        else{

            alvo->preco_final = (alvo->preco_base*(1.0 + (alvo->imposto/100)));
            *preco_total += alvo->preco_final;
        }
    }
}
//libera memória usada
void libera_memoria(produto *vetor, int n){

    for(int i = 0; i < n; i++){

        if(vetor[i].n_subprods != 0)
            free(vetor[i].ids_subprods);
    }
    free(vetor);
}
//-------------------------------------------------------------------------
int main(){

    int n; // quantidade de produtos a serem lidos
    int alvo; // produto que se deseja calcular o preço final
    float preco_total = 0; // marca preço total final
    float preco_atual = 0; // marca preço atual do calculo

    scanf(" %d", &n);

    produto* vetor = cria_vetor(n); // cria vetor

    for(int pos = 0; pos < n; pos++) // insere produtos
        insere(vetor, pos);

    scanf(" %d", &alvo);

    for(int i = 0; i < n; i++){ // calcula preço do produto alvo

        if(vetor[i].id_prod == alvo){

            calcula_preco(&vetor[i], vetor, vetor[i], &preco_total, &preco_atual, n, vetor[i]);
            break;
        }
    }

    printf("%.2f\n", preco_total); // saída

    libera_memoria(vetor, n); // libera memória usada

    
    return 0;
}