#include <stdio.h>
#include <stdlib.h>

#define TAM 12
#define PAI(x) ((x)-1)/2
#define FESQ(x) (2*(x)+1)
#define FDIR(x) (2*(x)+2)

typedef struct _Heap{
  int *array;
  int nelem;
  int tam;
}Heap;

Heap *heap;

void overflow(){

}
 
void subir(int pos){
  if(pos){
    int pai = PAI(pos);
    if(heap->array[pai] > heap->array[pos]){
      int t = heap->array[pos];
      heap->array[pos] = heap->array[pai];
      heap->array[pai] = t;
      subir(pai);
    }
  }
}

void insere(int x){
  if(heap->nelem == heap->tam){
    overflow();
  }
  if(heap->nelem < heap->tam){
    heap->array[heap->nelem] = x;
    subir(heap->nelem);
    heap->nelem++;
  }
}

// ----------------------
//    CRIA HEAP (5.1)
// ----------------------

void descer(int pos){
  int menor = -1;
  int esq = FESQ(pos);
  if(esq < heap->nelem){
    menor = esq;
    int dir = FDIR(pos);
    if(dir < heap->nelem && heap->array[esq] > heap->array[dir]){
      menor = dir;
    }
    if(heap->array[pos] > heap->array[menor]){
      int t = heap->array[pos];
      heap->array[pos] = heap->array[menor];
      heap->array[menor] = t;
      descer(menor);
    }
  }
}

void criaHeap(int array[], int nelem){
  heap = (Heap *)malloc(sizeof(Heap));
  heap->array = array;
  heap->nelem = nelem;
  for(int i = 0; i < nelem; i++){
    printf("%d ",heap->array[i]);
  }
  printf("\n");
  heap->tam = TAM;
  for(int i = PAI(nelem-1); i >= 0; i--){
    descer(i);
  }
}

// ----------------------------

void removeMin(){
  if(!heap->nelem){
    printf("Heap vazia\n");
    return;
  }
  heap->nelem--;
  heap->array[0] = heap->array[heap->nelem];
  descer(0);
}

int main(){
  int *array = (int *)malloc(TAM * sizeof(int));
  array[0] = 15;
  array[1] = 8;
  array[2] = 5;
  array[3] = 6;
  array[4] = 22;
  array[5] = 13;
  criaHeap(array,6);
  printf("Questão 5.2: ");
  for(int i = 0; i < heap->nelem; i++){
    printf("%d ",heap->array[i]);
  }
  printf("\n");
  insere(20);
  insere(7);
  insere(11);
  insere(18);
  printf("Questão 5.3: ");
  for(int i = 0; i < heap->nelem; i++){
    printf("%d ",heap->array[i]);
  }
  printf("\n");
  removeMin();
  printf("Questão 5.4: ");
  for(int i = 0; i < heap->nelem; i++){
    printf("%d ",heap->array[i]);
  }
  printf("\n");
  return 0;
}
