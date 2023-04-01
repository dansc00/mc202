#ifndef LAB07H
#define LAB07H

struct vet{

	int *vet; // apontador pro vetor
  int len; // tamanho do vetor
  int p_ocp; //posições ocupadas
  int *head; // cabeça
  int *tail; // cauda

} data;

int insert_first(struct vet *data, int valor);
int remove_first(struct vet *data);
int print_first(struct vet *data);
int insert_last(struct vet *data, int valor);
int remove_last(struct vet *data);
int print_last(struct vet *data);
int is_empty(struct vet *data);

#endif
