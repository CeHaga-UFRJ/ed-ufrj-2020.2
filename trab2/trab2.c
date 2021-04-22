#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBER_ID 1000000

int teams[MAX_NUMBER_ID+1];

typedef struct _element{
  int id;
  int team;
  struct _element *ant;
  struct _element *prox;
} element;

typedef struct _desc{
  int nTeams;
  element *head;
  element *tail;
  element **teamsTail;
} desc;

void cleanQueue(desc** teamQueue){
  element *aux = (*teamQueue)->head;
  while(aux != NULL){
    element *aux2 = aux;
    aux = aux->prox;
    free(aux2);
  }
  if((*teamQueue)->teamsTail != NULL) free((*teamQueue)->teamsTail);
  free(*teamQueue);
}

void initQueue(desc **teamQueue, int nTeams){
  if(*teamQueue != NULL) cleanQueue(teamQueue);
  *teamQueue = (desc *)malloc(sizeof(desc));
  (*teamQueue)->nTeams = nTeams;
  (*teamQueue)->head = (*teamQueue)->tail = NULL;
  (*teamQueue)->teamsTail = (element **)malloc(sizeof(element*)*(nTeams+1));
  for(int i = 0; i < nTeams+1; i++){
    (*teamQueue)->teamsTail[i] = NULL;
  }
}

int dequeue(desc* teamQueue){
  if(teamQueue == NULL) return -1;
  if(teamQueue->head == NULL) return -2;
  element *aux = teamQueue->head;
  int id = aux->id;
  teamQueue->head = teamQueue->head->prox;
  if(aux == teamQueue->tail){
    teamQueue->tail = NULL;
  }
  if(aux == teamQueue->teamsTail[aux->team]){
    teamQueue->teamsTail[aux->team] = NULL;
  }
  free(aux);
  return id;
}

void enqueue(desc* teamQueue, int id){
  element *x = (element *)malloc(sizeof(element));
  x->id = id;
  x->team = teams[id];
  if(teamQueue->head == NULL){
    teamQueue->head = x;
    x->ant = x->prox = NULL;
  }else if(teamQueue->teamsTail[teams[id]] == NULL){
    x->ant = teamQueue->tail;
    x->prox = NULL;
    x->ant->prox = x;
  }else{
    x->ant = teamQueue->teamsTail[teams[id]];
    x->prox = x->ant->prox;
    if(x->prox != NULL){
      x->prox->ant = x;
    }
    x->ant->prox = x;
  }
  if(x->prox == NULL) teamQueue->tail = x;
  teamQueue->teamsTail[teams[id]] = x;
}

int main(){
  int t;
  desc *teamQueue = NULL;
  scanf("%d",&t);
  int tt = 1;
  while(t != 0){
    printf("Scenario #%d\n",tt);
    for(int i = 0; i < t; i++){
      int n;
      scanf("%d",&n);
      while(n--){
        int a;
        scanf("%d",&a);
        teams[a]=i+1;
      }
    }
    initQueue(&teamQueue,t);
    char query[15];
    getchar();
    scanf("%s",query);
    while(strcmp(query,"STOP") != 0){
      if(strcmp(query,"DEQUEUE") == 0){
        int id = dequeue(teamQueue);
        printf("%d\n",id);
      } 
      else{
        int id;
        scanf("%d",&id);
        enqueue(teamQueue,id);
      }
      scanf("%s",query);
    }
    scanf("%d",&t);
    tt++;
    printf("\n");
  }
  return 0;
}