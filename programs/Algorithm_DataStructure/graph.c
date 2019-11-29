#include <stdio.h>

int main(){
  int i,j;
  int adj[100][100];
  int n,u,k,v;

  for(i=0;i<100;i++){for(j=0;j<100;j++){adj[i][j]=0;}}

  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&u);
    scanf("%d",&k);
    u--;
    for(j=0;j<k;j++){
      scanf("%d",&v);
      v--;
      adj[u][v]=1;
    }
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(j>0){printf(" ");}
      printf("%d",adj[i][j]);
    }
    printf("\n");
  }
  return 0;
}
