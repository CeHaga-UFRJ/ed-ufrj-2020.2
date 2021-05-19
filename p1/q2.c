#include <stdlib.h>
#include <stdio.h>

#define max(a,b) (a>b?a:b)

typedef struct _Node{
  int chave;
  int altura;
  struct _Node *esq;
  struct _Node *dir;
} Node;

// -----------------------------
//     PREENCHE ALTURA (2.1)
// -----------------------------

int getAltura(Node* node){
  if(node == NULL) return 0;
  return node->altura;
}

Node* preencheAltura(Node *node){
  if(node == NULL) return NULL;
  Node* aux = node;
  aux->esq = preencheAltura(node->esq);
  aux->dir = preencheAltura(node->dir);
  aux->altura = 1 + max(getAltura(aux->esq),getAltura(aux->dir));
  return aux;
}

// ---------------------
//      INSERE (2.2)
// ---------------------

Node* insere(Node *root, int x){
  if(root == NULL){
    root = (Node *)malloc(sizeof(Node));
    root->chave = x;
    root->esq = root->dir = NULL; 
  }else{
    if(x < root->chave){
      root->esq = insere(root->esq,x);
    }else{
      root->dir = insere(root->dir,x);
    }
  }
  root->altura = 1 + max(getAltura(root->esq),getAltura(root->dir));
  return root;
}

// ----------------------------

void imprime(Node *node){
  if(node != NULL){
    printf("Nó %d tem altura %d\n",node->chave, node->altura);
    imprime(node->esq);
    imprime(node->dir);
  }
}

int main(){
  Node *root = (Node *)malloc(sizeof(Node));
  root->chave = 5;
  root->esq = NULL;
  root->dir = (Node *)malloc(sizeof(Node));
  root->dir->esq = root->dir->dir = NULL;
  root->dir->chave = 10;
  imprime(root);
  printf("Preenche altura\n");
  root = preencheAltura(root);
  imprime(root);
  printf("Insere 3\n");
  root = insere(root, 3);
  imprime(root);
  printf("Insere 7\n");
  root = insere(root, 7);
  imprime(root);
  return 0;
}
