#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 61

// dados de nascimento
typedef struct Data{

    int dia;
    int mes;
    int ano;

}data;

// dados do aluno
typedef struct Aluno{

    char nome[MAX_NOME];
    int ra;
    data nascimento;

}aluno;

//cria vetor de alunos
aluno* cria_vetor(int n){
    
    aluno* vetor = (aluno*)malloc(n * sizeof(aluno)); // aloca memória para o vetor de alunos

    return vetor;
}

// insere aluno no vetor
void insere_aluno(aluno* vetor){

    aluno novo; // cria aluno novo
    
    scanf(" %d", &novo.ra);
    scanf(" %d %d %d", &novo.nascimento.dia, &novo.nascimento.mes, &novo.nascimento.ano);
    scanf(" %[^\n]", novo.nome);

    int i = 0;

    if(vetor[i].ra){ // procura espaço vazio no vetor

        while(vetor[i].ra){
            i++;
        }

        vetor[i] = novo;
    }
    else{

        vetor[i] = novo;
    }
}   
// algoritmo bubble sort para ordenação crescente de RA
void bubble_sort_ra(int n, aluno* vetor){

    aluno aux;

    for(int i = 1; i < n; i++){
        for(int j = 0; j < n-1; j++){

            if(vetor[j].ra > vetor[j+1].ra){

                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
}
// algoritmo bubble sort para ordenação crescente da data de nascimento
void bubble_sort_data(int n, aluno* vetor){

    aluno aux;

    for(int i = 1; i < n; i++){
        for(int j = 0; j < n-1; j++){

            if(vetor[j].nascimento.ano > vetor[j+1].nascimento.ano){

                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
            else if(vetor[j].nascimento.ano == vetor[j+1].nascimento.ano){

                if(vetor[j].nascimento.mes > vetor[j+1].nascimento.mes){

                    aux = vetor[j];
                    vetor[j] = vetor[j+1];
                    vetor[j+1] = aux;
                }
                else if(vetor[j].nascimento.mes == vetor[j+1].nascimento.mes){

                    if(vetor[j].nascimento.dia > vetor[j+1].nascimento.dia){

                        aux = vetor[j];
                        vetor[j] = vetor[j+1];
                        vetor[j+1] = aux;
                    }
                }
            }  
        }
    }
}
// algoritmo bubble sort para ordenação crescente do nome
void bubble_sort_nome(int n, aluno* vetor){

    aluno aux;

    for(int i = 1; i < n; i++){
        for(int j = 0; j < n-1; j++){

            if(strcmp(vetor[j].nome, vetor[j+1].nome) > 0){

                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
            }
        }
    }
}
// imprime saida
void imprime_saida(aluno* vetor, int n){

    for(int i = 0; i < n; i++){

        printf("%d ", vetor[i].ra);

        if(vetor[i].nascimento.dia < 10)
            printf("%d%d ", 0, vetor[i].nascimento.dia);
        else
            printf("%d ", vetor[i].nascimento.dia);
        
        if(vetor[i].nascimento.mes < 10)
            printf("%d%d ", 0, vetor[i].nascimento.mes);
        else
            printf("%d ", vetor[i].nascimento.mes);
        
        printf("%d ", vetor[i].nascimento.ano);
        printf("%s\n", vetor[i].nome);
    }
}
//-------------------------------------------------------------------------------------
int main(){

    int n; // numero de registros
    char param; // parametro escolhido para ordenação

    scanf(" %d", &n);

    aluno* vet = cria_vetor(n);

    for (int i = 0; i < n; i++)
        insere_aluno(vet);

    scanf(" %c", &param);

    switch(param){

        case 'R':

            bubble_sort_ra(n, vet);
        break;

        case 'D':

            bubble_sort_data(n, vet);
        break;

        case 'N':

            bubble_sort_nome(n, vet);
        break;
    }

    imprime_saida(vet, n);

    free(vet); // libera vetor

    return 0;
}