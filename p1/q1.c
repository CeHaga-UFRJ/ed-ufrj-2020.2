#include <stdlib.h>
#include <stdio.h>

typedef struct _element{
  int chave;
  struct _element *ant;
  struct _element *prox;
} element;

// ------------------------
//          BUSCA
// ------------------------
element* busca(element* head, int x){
  element *aux = head->prox;
  while(aux != head){
    if(aux->chave == x) return aux;
    aux = aux->prox;
  }
  return NULL;
}

// ------------------------
//          REMOCAO
// ------------------------
void remocao(element* head, int x){
  element *aux = head->prox;
  while(aux != head && aux->chave != x){
    aux = aux->prox;
  }
  if(aux == head) return;
  aux->ant->prox = aux->prox;
  aux->prox->ant = aux->ant;
  free(aux);
}

// -------------------------

int main(){
  element *head = (element *)malloc(sizeof(element));
  head->prox = (element *)malloc(sizeof(element));
  head->prox->prox = (element *)malloc(sizeof(element));
  head->ant = head->prox->prox;
  head->prox->ant = head;
  head->prox->chave = 5;
  head->ant->prox = head;
  head->ant->ant = head->prox;
  head->ant->chave = 8;
  element *aux = head->prox;
  while(aux != head){
    printf("%d ",aux->chave);
    aux = aux->prox;
  }
  printf("\n%d\n",busca(head,8)->chave);
  remocao(head,8);
  aux = head->prox;
  while(aux != head){
    printf("%d ",aux->chave);
    aux = aux->prox;
  }
  return 0;
}
