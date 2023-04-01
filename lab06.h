#ifndef LAB06C
#define LAB06C

struct node{

  int ind;
  struct node *next;

};
typedef struct node celula;

int add(celula **top, int n);
int mtf(celula *top, int *req, int r);
int tr(celula *top, int *req, int r);
/*int c();
*/
#endif
