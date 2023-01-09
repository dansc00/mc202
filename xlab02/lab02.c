#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FRASE 501
#define MAX_OCORR 31

void imprime_res(int ini, int fim, char frase[MAX_FRASE], char ocorr[MAX_OCORR], int n){

    for(int k = ini; k <= fim; k++){

        printf("%c", frase[k]);
    }

    printf("\n");

}

void imprime_fim(int ini, int fim, char frase[MAX_FRASE], char ocorr[MAX_OCORR], int n){

    if(fim < 10){

        printf("00%d ", fim+1);
    }
    else{

        printf("0%d ", fim+1);
    }

    imprime_res(ini, fim, frase, ocorr, n);
}

void imprime_ini(int ini, int fim, char frase[MAX_FRASE], char ocorr[MAX_OCORR], int n){

    if(ini < 10){

        printf("00%d ", ini+1);
    }
    else{

        printf("0%d ", ini+1);
    }

    imprime_fim(ini, fim, frase, ocorr, n);
}

void imprime_ocorr(int ini, int fim, char frase[MAX_FRASE], char ocorr[MAX_OCORR], int n){

    if(n < 10){

        printf("00%d ", n);
    }
    else{

        printf("0%d ", n);
    }

    imprime_ini(ini, fim, frase, ocorr, n);
}

int ocorre(char frase[MAX_FRASE], char ocorr[MAX_OCORR], int ini, int fim, int n, int opt){

    int cont;
    while(fim < strlen(frase)){

        for(int j = 0; j < strlen(ocorr); j++){

            if(frase[fim] == ocorr[j]){

                opt++;
                ini = fim;
                cont = 0;
                while(cont < (strlen(ocorr)-1) && frase[fim] != ' ' && frase[fim] != '.' && frase[fim] != '!' && frase[fim] != '?' && frase[fim] != ':'){

                    fim++;
                    cont++;
                }

                if(frase[fim] == ' ' || frase[fim] == '.' || frase[fim] == '!' || frase[fim] == '?' || frase[fim] == ':')
                    fim--;
                
                cont = 0;
                if(fim == ini){

                    while(cont < (strlen(ocorr)-1)){

                        cont++;
                        ini--;
                    }
                }
                imprime_ocorr(ini, fim, frase, ocorr, n);
                n++;
                break;
            }
        }
        fim++;
    }

    if(opt != 0)
        return 1;
    else
        return 0;
}

int main(){

    char frase[MAX_FRASE]; // entrada
    char ocorr[MAX_OCORR]; // ocorrência buscada

    fgets(frase, MAX_FRASE, stdin); // lê a entrada somente até 500 caracteres + \0
    scanf(" %s", ocorr);

    if(!ocorre(frase, ocorr, 0, 0, 1, 0))
        printf("Nenhuma ocorrencia encontrada\n");

    
    return 0;
}