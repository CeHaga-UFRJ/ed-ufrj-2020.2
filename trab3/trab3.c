#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (a>b?a:b)

typedef struct _node{
  struct _node *esq;
  struct _node *dir;
  int value;
  int height;
} node;

void printPreOrder(node* root){
  if(root){
    printf("%d\n",root->value);
    printPreOrder(root->esq);
    printPreOrder(root->dir);
  }
}

node* createNode(int value){
  node* element = (node *)malloc(sizeof(node));
  element->esq = element->dir = NULL;
  element->value = value;
  element->height = 1;
  return element;
}

int getHeight(node* element){
  if(!element) return 0;
  return element->height;
}

int getBalance(node* element){
  if(!element) return 0;
  return getHeight(element->esq) - getHeight(element->dir);
}

int newHeight(node* element){
  if(!element) return 0;
  return max(getHeight(element->esq),getHeight(element->dir)) + 1;
}

node* rotateEsq(node* element){
  node* child = element->dir;
  node* grand = child->esq;

  child->esq = element;
  element->dir = grand;
  
  element->height = newHeight(element);
  child->height = newHeight(child);
  
  return child;
}

node* rotateDir(node* element){
  node* child = element->esq;
  node* grand = child->dir;

  child->dir = element;
  element->esq = grand;

  element->height = newHeight(element);
  child->height = newHeight(child);

  return child;
}

node* insertElement(node* root, int value){
  if(!root){
    return createNode(value);
  }

  if(value < root->value){
    root->esq = insertElement(root->esq,value);
  }else{
    root->dir = insertElement(root->dir,value);
  }

  root->height = newHeight(root);
  int balance = getBalance(root);

  if(balance > 1){
    if(value < root->esq->value){
      return rotateDir(root);
    }else{
      root->esq = rotateEsq(root->esq);
      return rotateDir(root);
    }
  }else if(balance < -1){
    if(value < root->dir->value){
      root->dir = rotateDir(root->dir);
      return rotateEsq(root);
    }else{
      return rotateEsq(root);
    }
  }
  return root;
}

int main(){
  node* root = NULL;
  int n;
  while(scanf("%d",&n) == 1){
    root = insertElement(root,n);
  }
  printPreOrder(root);
}
