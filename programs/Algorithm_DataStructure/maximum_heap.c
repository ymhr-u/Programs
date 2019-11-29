#include <stdio.h>

#define MAX 500000
int h,a[MAX+1];

void maxHeapify(int i){
  int l,r,est,tmp;

  l=2*i;
  r=2*i+1;
  if(l<=h && a[l]>a[i]){est=l;}
  else{est=i;}
  if(r<=h && a[r]>a[est]){est=r;}
  if(est!=i){
    tmp=a[est];
    a[est]=a[i];
    a[i]=tmp;
    maxHeapify(est);
  }
}

int main(){
  int i;
  scanf("%d",&h);
  for(i=1;i<=h;i++) scanf("%d",&a[i]);
  for(i=h/2;i>=1;i--) maxHeapify(i);
  for(i=1;i<h+1;i++){
    if(i>0){printf(" ");}
    printf("%d",a[i]);
  }
  printf("\n");
  return 0;
}
