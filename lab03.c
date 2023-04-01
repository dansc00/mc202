#include <stdio.h>
#include <string.h>

int main(){

  int k, e;

  while((scanf("%d %d ", &k, &e)) == 2){

    char pchave[k][50], desc[e][101];

    for (int i = 0; i < k; i++){

      scanf("%s ", pchave[i]);

    }

    for (int j = 0; j < e; j++){

      scanf("%[^\n] ", desc[j]);

    }

  }

  char palavra;

  for (int i = 0; i < k; i++){

    do{

      char* p = pchave[i];
      palavra[i] = p;
      p++;

    } while(p != '\0')

    for (int j = 0; j < e; j++){

      if ((strstr(palavra, desc[j])) != NULL){
        
      }


    }


  }






  return 0;

}
