// lab 01 MC-202 Daniel de Sousa Cipriano 233228

#include <stdio.h>

int main(){

  int n,m,r,s;
  scanf("%i %i %i %i", &n, &m, &r, &s); // n = linhas, m = colunas(matriz principal). r = linhas, s = colunas (submatriz)

  int i, j, matriz[n][m];

  for(i = 0; i < n; i++){ // percorre as linhas da matriz
    for(j = 0; j < m; j++){ // percorre as colunas da matriz
      scanf("%i", &matriz[i][j]); // lê cada elemento das linhas e colunas
    }
  }

  i = j = 0;
  int max = 0;
  int aux = 0;
  do{
    do{
      for(i ; i < r; i++){
        if(j == s){
          j = s-r;
        }
        for(j ; j < s; j++){
          aux += matriz[i][j];
        }
      }

      i = j = 0;
      if(aux > max){
        max = aux;
        aux = 0;
      }
      else{
        aux = 0;
      }
      j++;
      s++;
    } while(j < m-2);
    j = s = 0;
    i++;
    r++;
  } while(i < n);

  printf("%i", max);
  return 0;
}
