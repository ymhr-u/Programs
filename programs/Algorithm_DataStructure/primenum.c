#include<stdio.h>
int prime(int x);

int main (){
  int i,n,a[10001],count=0;

  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&a[i]);
    count+=prime(a[i]);
  }
  printf("%d\n",count);
  return 0;
}

int prime(int x){
  int i;
  if(x==2)return 1;
  else if(x%2==0||x==1)return 0;

  for(i=3;i*i<x+1;i++){
    if(x%i==0)return 0;
  }
  return 1;
}
