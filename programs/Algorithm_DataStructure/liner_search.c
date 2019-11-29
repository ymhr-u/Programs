#include<stdio.h>
int search(int key);

int a[10001],n;

int main(){
  int i,m,q,sum=0;

  scanf("%d",&n);
  for(i=0;i<n;i++){scanf("%d",&a[i]);}

  scanf("%d",&m);
  for(i=0;i<m;i++){
    scanf("%d",&q);
    a[n]=q;
    if(search(q)){sum++;}
  }
  printf("%d\n",sum);
  return 0;
}



int search(int key){
  int i=0;
  while(a[i]!=key)i++;
  if(i==n)return 0;
  else return 1;
}
