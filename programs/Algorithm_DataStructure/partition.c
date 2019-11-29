#include<stdio.h>
int partition(int *A,int p,int r);

int main(){
  int i,x,n,A[100001];
  scanf("%d",&n);
  for(i=0;i<n;i++){scanf("%d",&A[i]);}

  x=partition(&A,0,n-1);
  for(i=0;i<x;i++){printf("%d ",A[i]);}
  printf("[%d]",A[i]);
  i++;
  for(i;i<n;i++){printf(" %d",A[i]);}
  printf("\n");
}

int partition(int *A,int p,int r){
  int i,j,tmp,x;
  x=A[r];
  i=p-1;
  for(j=p;j<r;j++){
    if(A[j]<=x){
      i++;
      tmp=A[i];
      A[i]=A[j];
      A[j]=tmp;
    }
  }
  tmp=A[i+1];
  A[i+1]=A[r];
  A[r]=tmp;
  return i+1;
}
