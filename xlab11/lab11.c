#include <stdio.h>
#include <stdlib.h>

// imprime saida
void imprime(int *v, int k){

    for(int i = 0; i < k; i++)
        printf("%d ", v[i]);

    printf("\n");
}

// copia vetor v1 para v2
void copia_vetor(int *v1, int *v2, int k){

    for(int i = 0; i < k; i++){

        v2[i] = v1[i];
    }
}

// algoritmo de ordenação bubble sort com os limites da sublista 
void bubble_sort(int *v, int l, int r){

    int aux;

    for(int i = l; i < r; i++){
        for(int j = r; j > i; j--){

            if(v[j] < v[j-1]){

                aux = v[j];
                v[j] = v[j-1];
                v[j-1] = aux;
            }
        }
    }
}

void merge(int *v, int l, int m, int r, int n){

    int aux[n];
    int i = l, j = m + 1, k = 0;

    while(i <= m && j <= r){

        if(v[i] <= v[j]){

            aux[k] = v[i];
            k++;
            i++;
        } 
        else{

            aux[k] = v[j];
            k++;
            j++;
        }
    }

    while(i <= m){

        aux[k] = v[i];
        k++;
        i++;
    }

    while(j <= r){

        aux[k] = v[j];
        k++;
        j++;
    }

    for(i = l, k = 0; i <= r; i++, k++){

        v[i] = aux[k];
    }
}

// algoritmo de ordenação mergesort
void mergesort(int *v, int l, int r, int x, int k){

    imprime(v, k);

    if(r - l <= x){ // caso a sublista seja menor ou igual ao limite x

        bubble_sort(v, l, r);
    }
    else{

        int m = (l + r)/2;

        if(l < r){

            mergesort(v, l, m, x, k);
            mergesort(v, m+1, r, x, k);
            merge(v, l, m, r, k);    
        }
    }   
}

int particiona(int *v, int l, int r){

    int pivo = v[l], pos = r+1, aux;

    for(int i = r; i >= l; i--){

        if(v[i] >= pivo){

            pos--;
            aux = v[i];
            v[i] = v[pos];
            v[pos] = aux;
        }
    }

    return pos;
}

// algoritmo de ordenação quicksort
void quicksort(int *v, int l, int r, int k, int x){

    imprime(v, k);

    if(r - l <= x){ // caso a sublista seja menor ou igual que o limite x

        bubble_sort(v, l, r);
    }
    else{

        if(r <= l)
            return;

        int i = particiona(v, l, r);
        quicksort(v, l, i-1, k, x);
        quicksort(v, i+1, r, k, x);
    }
}

int main(){

    int *v_merge, *v_quick, k; // vetores de elementos, numero de elementos do vetor
    int x; // quantidade de elementos  para ordenação por divisão e conquista

    scanf(" %d", &k);

    v_merge = (int*)malloc(k * sizeof(int)); // aloca vetor para o mergesort
    v_quick = (int*)malloc(k * sizeof(int)); // aloca vetor para o quicksort

    for(int i = 0; i < k; i++){ // lê entrada

        scanf(" %d", &v_merge[i]);
    }

    copia_vetor(v_merge, v_quick, k); // copia elementos do vetor

    scanf(" %d", &x);

    // mergesort
    printf("MERGESORT\n");
    mergesort(v_merge, 0, k-1, x, k);
    imprime(v_merge, k);

    // quicksort
    printf("QUICKSORT\n");
    quicksort(v_quick, 0, k-1, k, x);
    imprime(v_quick, k);

    // libera memória
    free(v_merge);
    free(v_quick);

    return 0;
}


