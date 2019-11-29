#include <stdio.h>
#include <stdlib.h>

int main(){
  int n,i,j,C[10001];
  int *A,*B;
  scanf("%d",&n);
  A = malloc(sizeof(int)*n+1);
  B = malloc(sizeof(int)*n+1);

  for(i=0 ; i<=10000 ; i++){C[i]=0;}
  for(i=1 ; i<=n ; i++){
    scanf("%d",&A[i]);
    C[A[i]]++;
  }
  for(i=1;i<=10000;i++){C[i]+=C[i-1];}
  for (j=1;j<=n;j++){
    B[C[A[j]]]=A[j];
    C[A[j]]--;
  }
  for(i=1;i<n;i++){printf("%d ",B[i]);}
  printf("%d\n",B[n]);

  return 0;
}
