#include <stdlib.h>

#define MAX 100
#define WHITE 0
#define GRAY 1
#define BLACK 2

int n,M[MAX][MAX];

int prim(){
  int u,minv,v,sum=0;
  int i,d[MAX],p[MAX],col[MAX];
  for(i=0;i<n;i++){
    d[i]=9999;
    p[i]=-1;
    col[i]=WHITE;
  }
  d[0]=0;

  while(1){
    minv=9999;
    u=-1;
    for(i=0;i<n;i++){
      if(minv>d[i] && col[i]!=BLACK){
        u=i;
        minv=d[i];
      }
    }
    if(u==-1) break;
    col[u]=BLACK;
    for(v=0;v<n;v++){
      if(col[v]!=BLACK && M[u][v]!=10000){
        if(d[v]>M[u][v]){
          d[v]=M[u][v];
          p[v]=u;
          col[v]=GRAY;
        }
      }
    }
  }
  sum=0;
  for(i=0;i<n;i++){if(p[i]!=-1) sum+=M[i][p[i]];}
  return sum;
}

int main(){
  int i,j,e;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      scanf("%d",&e);
      if(e==-1){
        M[i][j]=10000;
      }else M[i][j]=e;
    }
  }
  printf("%d\n",prim());
  return 0;
}
