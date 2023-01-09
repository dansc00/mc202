#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Hash{ // guarda tabela hash

    long long int *t_hash; // tabela hash
    int m; // tamanho do hash

} hash;

#define MAX_PALAVRA 21 // tamanho máximo da palavra passada na entrada
#define MAX_HASH 50 // tamanho máximo da tabela hash

//-------------  fim da definição -----------------------

// inicializa hash
hash* cria_hash(int m){

    hash *h = (hash*)malloc(sizeof(hash));

    h->m = m;
    h->t_hash = (long long int*)malloc(h->m * sizeof(long long int));   

    return h;
}

// converte a palavra passada para seu valor numérico
long long int converte_numerico(char* palavra, int m){

    long long int val = 0;
    int pot = strlen(palavra) - 1;

    for(int i = 0; palavra[i] != '\0'; i++){

        val += (palavra[i] * pow(256, pot));
        pot--;
    }

    return val;
}

// função de hashing
int hashing(int a, int b, long long int k, int p, int m){

    return ((a*k + b) % p) % m;
}

// insere na tabela hash
hash* insere(hash* h, int a, int b, long long int k, int p, int m){

    int chave = hashing(a, b, k, p, m);

    if(h->t_hash[chave] > 0){ // caso a posição não seja vazia

        do{ // percorre até a próxima posição vazia
            chave++;

            if(chave >= m)
                chave = 0;


        } while(h->t_hash[chave] != 0);
    }
    
    h->t_hash[chave] = k;

    return h;
}

// remove elemento do hash com valor dummy, valor dummy = -1
hash* remove_com_dummy(hash* h, int a, int b, long long int k, int p, int m){

    int chave = hashing(a, b, k, p, m);
    int pos = chave; // percorre posições da tabela

    if(h->t_hash[chave] == k){ // caso elemento está na posição chave

        h->t_hash[chave] = -1;
    }
    else{ // caso não percorre até encontrar o elemento

        do{

            pos++;

            if(pos >= m)
                pos = 0;


        } while(h->t_hash[pos] != k);

        h->t_hash[pos] = -1; // atribui dummy
    }

    return h;
}

// remove elemento da tabela com rehash, valor vazio = 0
hash* rehash(hash *h, int a, int b, long long int k, int p, int m){

    int chave = hashing(a, b, k, p, m);

    int pos_hash = chave; // posição no hash
    int pos_aux = 0; // posição no vetor auxiliar
    int pos_removida; // marca posição em que estava o elemento removido
    int n_removidos = 0; // número de elementos removidos

    long long int *aux = malloc(m * sizeof(long long int)); // vetor auxiliar, armazena valores removidos do hash

    if(h->t_hash[chave] == k){ // se o elemento está na posição chave

        h->t_hash[chave] = 0;
        pos_removida = chave;
    }
    else{ // senão, percorre até encontrar

        do{
            pos_hash++;

            if(pos_hash >= m)
                pos_hash = 0;


        } while(h->t_hash[pos_hash] != k);

        h->t_hash[pos_hash] = 0; // atribui vazio
        pos_removida = pos_hash;
    }

    do{ // insere valores no vetor auxiliar

        pos_hash++;

        if(pos_hash >= m)
            pos_hash = 0;

        if(h->t_hash[pos_hash] != 0){

            aux[pos_aux] = h->t_hash[pos_hash];
            h->t_hash[pos_hash] = 0;
            n_removidos++;
            pos_aux++;
        }

    } while(pos_hash != pos_removida);

    pos_aux = 0;

    while(n_removidos > 0){ // reinsere valores removidos

        h = insere(h, a, b, aux[pos_aux], p, m);
        pos_aux++;
        n_removidos--;
    }

    free(aux);

    return h;
}

// imprime saida
void saida(hash *h1, hash *h2, int m){

    printf("---------------------------------------------\n");
    printf(" rehash               | dummy                \n");
    printf("---------------------------------------------\n");

    for(int i = 0; i < m; i++){

        if(h2->t_hash[i] != 0)
            printf(" %-20lld |", h2->t_hash[i]);
        else
            printf(" %-20s |", "VAZIO");

        
        if(h1->t_hash[i] > 0)
            printf(" %-20lld \n", h1->t_hash[i]);
        else if(h1->t_hash[i] == 0)
            printf(" %-20s \n", "VAZIO");
        else    
            printf(" %-20s \n", "DUMMY");  
    }
}
// ----------------------- fim da implementação----------------------------------

int main(){

    int m; // tamanho do hash
    int p, a, b; // parâmetros para a função de hash
    int n; // numero de palavras a serem lidas
    int k; // numero de palavras a serem removidas

    char* palavra = (char*)malloc(MAX_PALAVRA * sizeof(char)); // palavra a ser lida na entrada
    long long int val; // valor numérico da palavra

    hash *h1, *h2; // hash com dummy, hash sem dummy

    scanf(" %d %d %d %d", &m, &p, &a, &b);

    h1 = cria_hash(m);
    h2 = cria_hash(m);

    scanf(" %d", &n);

    for(int i = 0; i < n; i++){

        scanf(" %20s", palavra);

        val = converte_numerico(palavra, m);

        h1 = insere(h1, a, b, val, p, m);
        h2 = insere(h2, a, b, val, p, m);
    }

    scanf(" %d", &k);

    for(int j = 0; j < k; j++){

        scanf(" %20s", palavra);

        val = converte_numerico(palavra, m);

        h1 = remove_com_dummy(h1, a, b, val, p, m);
        h2 = rehash(h2, a, b, val, p, m);
    }

    saida(h1, h2, m);

    // libera memória
    free(palavra);
    free(h1->t_hash);
    free(h2->t_hash);
    free(h1);
    free(h2);

    return 0;
}