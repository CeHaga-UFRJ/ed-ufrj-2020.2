#include <stdio.h>

#define N 51234

int pai[N], tam[N], rep[N];

int find(int x){
  if(x == pai[x]) return x;
  return pai[x] = find(pai[x]); 
}

void join(int a, int b){
  a = find(a);
  b = find(b);

  if(tam[a] <= tam[b]){
    pai[a] = b;
    tam[b] += tam[a];
  }else{
    pai[b] = a;
    tam[a] += tam[b];
  }
}

int main(){
  int n, m;
  scanf("%d%d",&n,&m);
  for(int tt = 1; n != 0; tt++){
    for(int i = 1; i < n+1; i++){
      pai[i] = i;
      tam[i] = 1;
      rep[i] = 0;
    }
    for(int i = 0; i < m; i++){
      int a,b;
      scanf("%d%d",&a,&b);
      join(a,b);
    }
    int total = 0;
    for(int i = 1; i < n+1; i++){
      int x = find(i);
      if(rep[x] == 0) total++;
      rep[x] = 1;
    }
    printf("Case %d: %d\n",tt,total);
    scanf("%d%d",&n,&m);
  }
  return 0;
}
