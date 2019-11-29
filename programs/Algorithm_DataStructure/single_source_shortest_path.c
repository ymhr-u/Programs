#include <stdio.h>

int n,M[100][100];
void diks(){
  int minv,i,v,u;
  int d[100],col[100];

  for(i=0;i<n;i++){
    d[i]=999999;
    col[i]=0;
  }

  d[0]=0;
  col[0]=1;
  while(1){
    minv=999999;
    u=-1;
    for(i=0;i<n;i++){
      if(minv>d[i] && col[i]!=2){
        u=i;
        minv=d[i];
      }
    }
    if(u==-1) break;
    col[u]=2;
    for(v=0;v<n;v++){
      if(col[v]!=2 && M[u][v]!=999999){
        if(d[v] > d[u]+M[u][v]){
          d[v]=d[u]+M[u][v];
          col[v]=1;
        }
      }
    }
  }
  for(i=0;i<n;i++){
    printf("%d ",i);
    if(d[i]==999999){printf("1\n");}
    else{printf("%d\n",d[i]);}
  }
}

int main(){
  int i,j,u,k,v,c;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      M[i][j]=999999;
    }
  }
  for(i=0;i<n;i++){
    scanf("%d %d",&u,&k);
    for(j=0;j<k;j++){
      scanf("%d %d",&v,&c);
      M[u][v]=c;
    }
  }
  diks();
  return 0;
}
