#include<stdio.h>

int N=100;
int min(int x,int y){
  if(x<=y) return x;
  else return y;
}

int main(){
  int n,p[N+1],m[N+1][N+1],i,j,k,l;
  scanf("%d",&n);
  for(i=1;i<=n;i++){
    scanf("%d",&p[i-1]);
    scanf("%d",&p[i]);
  }

  for(i=1;i<=n;i++) m[i][i]=0;
  for(l=2;l<=n;l++){
    for(i=1;i<=n-l+1;i++){
      j=i+l-1;
      m[i][j]=99999999;
      for(k=i;k<=j-1;k++){ m[i][j]= min(m[i][j] , m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j]);}
    }
  }
  printf("%d\n",m[1][n]);

  return 0;
}
