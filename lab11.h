#ifndef LAB11H
#define LAB11H

typedef struct string{

  char str[251]; // vetor que armazena a cadeia de caracteres
  int id; // identificador de cada cadeia

}string;

typedef struct tab_hash{

  int len_tab; // tamanho da tabela hash
  int p_ocp; // posições ocupadas na tabela

  struct string **elem; // apontador para apontadores de struct string, representa os elementos da tabela

} hash;

int hash1_divisao(int len_tab, char *str);
int hash2_multiplicacao(int len_tab, char *str);
unsigned long conversor(unsigned char *str);
string* busca(hash *ha, char *str);
int inserir(hash **ha, char *str);
int remover(hash **ha, char *str);
int liberar(hash *ha);


#endif
