#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXP 241 // tamanho maximo para a entrada

typedef struct Pilha_de_operadores{ // pilha que armazena operadores

    char ops; // operador
    int prioridade; // prioridade do operador

    struct Pilha_de_operadores *prox_ops;

} pilha_ops;

typedef struct Pilha_de_algarismos{ // pilha que armazena algarismos

    float alg; // valor do algarismo

    struct Pilha_de_algarismos *prox_alg;

} pilha_alg;
// ----------- fim da definição -------------------------------

// testa se existe divisão por zero
int testa_divisao_por_zero(char *exp){

    int pos = 0;
    char atual = exp[pos];

    while(atual != '\0'){

        if(atual == ' '){

            pos++;
            atual = exp[pos];
            continue;
        }

        if(atual == '/'){

            if(exp[pos+2] == '0')
                return 0; 
        }

        pos++;
        atual = exp[pos];
    }

    return 1;
}

// inicializa pilha de algarismos
pilha_alg* cria_pilha_alg(){

    return NULL;
}

// inicializa pilha de operadores
pilha_ops* cria_pilha_ops(){

    return NULL;
}

// empilha algarismo passado por parâmetro
pilha_alg* empilha_algarismo(pilha_alg* topo, float alg){

    pilha_alg* novo = (pilha_alg*)malloc(sizeof(pilha_alg));

    novo->alg = alg;
    novo->prox_alg = topo;
    
    return novo;
}

// empilha operador passado por parâmetro
pilha_ops* empilha_operador(pilha_ops* topo, char ops){

    pilha_ops* novo = (pilha_ops*)malloc(sizeof(pilha_ops));

    novo->ops = ops;

    switch(ops){ // define prioridade do operador

        case '*':
            novo->prioridade = 2;
        break;

        case '/':
            novo->prioridade = 2;
        break;

        case '-':
            novo->prioridade = 1;
        break;

        case '+':
            novo->prioridade = 1;
        break;        
    }
    novo->prox_ops = topo;
    
    return novo;
}

// desempilha pilha de algarismos
pilha_alg* desempilha_algarismo(pilha_alg* topo){

    pilha_alg* desempilhado = topo;
    topo = topo->prox_alg;
    free(desempilhado);

    return topo;
}

// desempilha pilha de operadores
pilha_ops* desempilha_operador(pilha_ops* topo){

    pilha_ops* desempilhado = topo;
    topo = topo->prox_ops;
    free(desempilhado);

    return topo;
}

// testa se a prioridade do operador no parâmetro é menor ou igual a prioridade do operador da pilha
int testa_prioridade(pilha_ops* topo, char atual){

    int prioridade_atual;

    switch(atual){

        case '*':
            prioridade_atual = 2;
        break;

        case '/':
            prioridade_atual = 2;
        break;

        case '+':
            prioridade_atual = 1;
        break;

        case '-':
            prioridade_atual = 1;
        break;
    }

    if(prioridade_atual <= topo->prioridade)
        return 1;

    return 0;
}

// imprime em notação pós fixa e retorna a expressão nessa notação
void imprime_e_converte_posfixa(pilha_ops* pilha_ops, char* exp, char* exp_posfix){

    int pos = 0; // posição na expressão
    char atual = exp[pos]; // caracter atual da expressão

    int pos_posfix = 0; // posição na expressão pós fixa

    while(atual != '\0'){ // percorre até o fim da expressão

        if(atual == ' '){ // caracter atual é espaço

            pos++;
            atual = exp[pos];
            continue;
        }

        if(atual == '*' || atual == '/' || atual == '+' || atual == '-'){ // caracter atual é operador

            if(pilha_ops){ // se existe elemento na pilha de operadores
                
                while(pilha_ops && testa_prioridade(pilha_ops, atual)){ 

                    printf("%c ", pilha_ops->ops);
                    exp_posfix[pos_posfix] = pilha_ops->ops;
                    pos_posfix++;

                    pilha_ops = desempilha_operador(pilha_ops);
                }
                
                pilha_ops = empilha_operador(pilha_ops, atual);
            }
            else{

                pilha_ops = empilha_operador(pilha_ops, atual);
            }
        }
        else{ // caracter atual é algarismo

            printf("%c ", atual);
            exp_posfix[pos_posfix] = atual;
            pos_posfix++;
        }

        pos++;
        atual = exp[pos];
    }

    while(pilha_ops){ // termina de printar pilha

        if(pilha_ops->prox_ops){

            printf("%c ", pilha_ops->ops);
            exp_posfix[pos_posfix] = pilha_ops->ops;
            pos_posfix++;

            pilha_ops = desempilha_operador(pilha_ops);
        }
        else{ // caso seja ultimo elemento na pilha

            printf("%c\n", pilha_ops->ops);
            exp_posfix[pos_posfix] = pilha_ops->ops;
            pos_posfix++;

            pilha_ops = desempilha_operador(pilha_ops);
        }
    }
}
 // calcula e imprime resultado da expressão
void calcula_expressao(pilha_alg* pilha_alg, char* exp_posfix){

    int pos = 0; // posição atual na expressão pósfixa
    char atual = exp_posfix[pos]; // marca elemento atual na expressão posfixa

    float val1, val2, res; // valores a serem lidos da pilha e resultado da operação

    while(atual != '\0'){ // percorre até o fim da expressão

        if(atual == '*' || atual == '/' || atual == '+' || atual == '-'){ // caso operador

            switch(atual){ // desempilha 2 valores e realiza a operação exigida salvando o resultado

                case '*': 

                    val1 = pilha_alg->prox_alg->alg;
                    val2 = pilha_alg->alg;

                    res = val1 * val2;

                    pilha_alg = desempilha_algarismo(pilha_alg);
                    pilha_alg = desempilha_algarismo(pilha_alg);

                    pilha_alg = empilha_algarismo(pilha_alg, res); 
                break;

                case '/': 

                    val1 = pilha_alg->prox_alg->alg;
                    val2 = pilha_alg->alg;

                    res = val1 / val2;

                    pilha_alg = desempilha_algarismo(pilha_alg);
                    pilha_alg = desempilha_algarismo(pilha_alg);

                    pilha_alg = empilha_algarismo(pilha_alg, res);
                break;

                case '+':

                    val1 = pilha_alg->prox_alg->alg;
                    val2 = pilha_alg->alg;

                    res = val1 + val2;

                    pilha_alg = desempilha_algarismo(pilha_alg);
                    pilha_alg = desempilha_algarismo(pilha_alg);

                    pilha_alg = empilha_algarismo(pilha_alg, res);
                break;

                case '-':

                    val1 = pilha_alg->prox_alg->alg;
                    val2 = pilha_alg->alg;

                    res = val1 - val2;

                    pilha_alg = desempilha_algarismo(pilha_alg);
                    pilha_alg = desempilha_algarismo(pilha_alg);

                    pilha_alg = empilha_algarismo(pilha_alg, res);
                break;
            }
        }
        else{

            pilha_alg = empilha_algarismo(pilha_alg, atual - '0'); // empilha algarismo transformando em float
        }

        pos++;
        atual = exp_posfix[pos];
    }

    printf("%.2f\n", pilha_alg->alg); // printa resultado

    pilha_alg = desempilha_algarismo(pilha_alg); // desempilha ultimo elemento
}

// --------------------- fim da implementação de funções -----------------------------------
int main(){

    char *exp = (char*)malloc(MAX_EXP * sizeof(char)); // aloca expressão
    scanf(" %241[^\n]", exp); // recebe expressão

    pilha_alg* topo_alg = cria_pilha_alg(); // inicializa pilha de algarismos
    pilha_ops* topo_ops = cria_pilha_ops(); // inicializa pilha de operadores

    char *exp_posfix = (char*)malloc((strlen(exp)+1) * sizeof(char)); // aloca expressão pós fixa

    if(!testa_divisao_por_zero(exp)){ // testa se existe divisão por zero

        printf("ERRO: DIVISAO POR ZERO ENCONTRADA.\n");
    }
    else{

        imprime_e_converte_posfixa(topo_ops, exp, exp_posfix);
        calcula_expressao(topo_alg, exp_posfix);
    }

    // libera memória das expressões armazenadas
    free(exp);
    free(exp_posfix);

    return 0;
}