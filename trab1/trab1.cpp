#include <bits/stdc++.h>
using namespace std;

#define MAXN 10000

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
};

void mergeSortRec(int v[], int aux[], int ini, int fim){
  int m = (ini+fim)/2;
  if(ini < fim){
    mergeSortRec(v, aux, ini, m);
    mergeSortRec(v, aux, m+1, fim);
    merge(v, aux, ini, fim);
  }
};

void mergeSort(int v[], int n){
  int aux[MAXN];
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
	int n = 0;
	int array[MAXN];
	while(scanf("%d",&array[n]) == 1) n++;

  if(argc == 1){
    printf("Usando a ordenação SelectionSort\n");
    selectionSort(array,n);
  }else{
    if(strcmp(argv[1],"-q") == 0){
    printf("Usando a ordenação QuickSort\n");
      quicksort(array,n);
    }
    if(strcmp(argv[1],"-m") == 0){
    printf("Usando a ordenação MergeSort\n");
      mergeSort(array,n);
    }
  }

	for(int i = 0; i < n; i++){
		printf("%d\n",array[i]);
	}
	return 0;
}