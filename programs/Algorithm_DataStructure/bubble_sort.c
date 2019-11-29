#include <stdio.h>
int BubbleSort(int *a,int b);

int main(int argc, const char * argv[]) {
  int a[100],n,i;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&a[i]);
  }
  printf("%d\n",BubbleSort(&a,n));
}

int BubbleSort(int *a,int n){
  int i,tmp,count=0 ;
  int flag = 1;
    
  while(flag){
    flag=0;
    for(i=n-1;i>=1;i--){
      if(a[i]<a[i-1]){
	count++;
	tmp=a[i];
	a[i]=a[i-1];
	a[i-1]=tmp;
	flag=1;
      }
    }
  }
  for(i=0;i<n-1;i++){
    printf("%d ",a[i]);
  }
  printf("%d\n",a[i]);
  return count;
}
