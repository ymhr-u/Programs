#include<stdio.h>
int devcon(int i,int x);

int n,a[21];

int main(){
  int i,m,x,result;
  scanf("%d",&n);
  for(i=0;i<n;i++){scanf("%d",&a[i]);}
  scanf("%d",&m);
  for(i=0;i<m;i++){
    scanf("%d",&x);
    result=devcon(0,x);
    if(result)printf("yes\n");
    else printf("no\n");
  }
}

int devcon(int i,int x){
  int result;
  if(x==0)return 1;
  if(i>=n)return 0;
  result = devcon(i+1,x)||devcon(i+1,x-a[i]);
  return result;
}
