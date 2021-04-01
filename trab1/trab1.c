#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8

void overflow(int **v, int *tam){
  int *tmp = (int *)malloc(sizeof(int) * 2 * (*tam));
  for(int i = 0; i < (*tam); i++){
    tmp[i] = (*v)[i];
  }
  (*tam) *= 2;
  free((*v));
  (*v) = tmp;
}

// --------------------------
//       SELECTION SORT
// --------------------------
void selectionSort(int v[], int n){
	for(int i = 0; i < n-1; i++){
		for(int j = i+1; j < n; j++){
			if(v[i] > v[j]){
				int t = v[i];
				v[i] = v[j];
				v[j] = t;
			}
		}
	}
}

// ---------------------
//       MERGE SORT
// ---------------------

void merge(int v[], int aux[], int ini, int fim){
  int m = (ini+fim)/2;
  int esq, dir, k;
  
  for(esq = ini, dir = m+1, k = 0; esq <= m && dir <= fim; k++){
    if(v[esq] < v[dir]){
      aux[k] = v[esq++];
    }else{
      aux[k] = v[dir++];
    }
  }

  while(esq <= m){
    aux[k++] = v[esq++];
  }

  while(dir <= fim){
    aux[k++] = v[dir++];
  }

  for(int i = ini; i <= fim; i++){
    v[i] = aux[i-ini];
  }
}

void mergeSortRec(int v[], int aux[], int ini, int fim){
  int m = (ini+fim)/2;
  if(ini < fim){
    mergeSortRec(v, aux, ini, m);
    mergeSortRec(v, aux, m+1, fim);
    merge(v, aux, ini, fim);
  }
}

void mergeSort(int v[], int n){
  int *aux = (int *)malloc(sizeof(int) * n);
  mergeSortRec(v, aux, 0, n-1);
}


// ------------------
//     QUICK SORT
// ------------------

void quickSortRec(int v[], int ini, int fim){
  int esq = ini;
  int dir = fim-1;
  int m = (ini+fim)/2;
  int pivot = v[m];
  while(esq <= dir){
    while(esq <= fim-1 && v[esq] < pivot) esq++;
    while(dir >= ini && v[dir] > pivot) dir--;
    if(esq <= dir){
      int t = v[esq];
      v[esq] = v[dir];
      v[dir] = t;
      esq++;
      dir--;
    }
  }
  if(dir > ini) quickSortRec(v,ini,dir+1);
  if(esq < fim) quickSortRec(v,esq,fim);
}

void quicksort(int v[], int n){
  quickSortRec(v,0,n);
}

// ----------------
//       MAIN
// ----------------

int main(int argc, char **argv){
	int n = N;
	int *array = (int *)malloc(sizeof(int)*n);
  int num;
  int k = 0;
	while(scanf("%d",&num) == 1){
    if(n == k+1){
      overflow(&array,&n);
    }
    array[k++] = num;
  }

  if(argc == 1){
    selectionSort(array,k);
  }else{
    if(strcmp(argv[1],"-q") == 0){
      quicksort(array,k);
    }
    if(strcmp(argv[1],"-m") == 0){
      mergeSort(array,k);
    }
  }

  for(int i = 0; i < k; i++){
    printf("%d\n",array[i]);
  }
  return 0;
}