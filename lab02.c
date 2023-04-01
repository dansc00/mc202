// Lab 02 MC202 Daniel de Sousa Cipriano 233228

#include <stdio.h>

int main(){

  int c, n, t, d, tesp, auxd, auxt; // c n de atendentes, n n de clientes
  int soma = 0;
  int m10 = 0;
  int auxc = 0;
  int auxn = 0;
  int cond = 0;
  float media;

  scanf("%i %i", &c, &n);
  int atend[1000][2] = {0};

  for (int x = 0; x < n; x++){ // percorre o número de clientes
    scanf("%i %i", &t, &d);

    if (x == 0){ // primeira iteração não necessita verificação
      auxt = t;
      auxd = d;
      continue;
    }
    else{
      tesp = auxd - (t - auxt);
      if (tesp > 0 && atend[c-1][-1] == 0){ // se haveria tempo de espera, porém haviam atendentes livres
        atend[auxc][0] = t; // próxima linha recebe t e d
        atend[auxc][1] = d;
        auxc++;
      }
      else if (tesp > 0 && atend[c-1][-1] != 0){ // se todas atendentes estão ocupadas
        for (int i = 0; i < c; i++){ // percorre a lista
          if (t-atend[i][0] > atend[i][1]){ // se a atendente já está liberada
            atend[i][0] = t; // adiciona novo t e d
            atend[i][1] = d;
            cond = 1;
            break;
          }
        }
        if (cond != 1 && tesp > 10){ // se todas atendentes estavam ocupadas e o tempo de espera é maior que 10 minutos
          soma += tesp;
          auxn++;
          m10++;
          cond = 0;
        }
        else if (cond != 1 && tesp < 10){ // se todas atendentes estão ocupadas e o tempo de espera é menor que 10 minutos
          soma += tesp;
          auxn++;
          cond = 0;
        }

      }
    auxt = t;
    auxd = d;
    }
  }
  media = soma/auxn;
  printf("Espera media para %i clientes: %f minutos\n", auxn, media);
  printf("Numeros de clientes que esperaram mais que 10 minutos: %i\n", m10);

  return 0;
}
