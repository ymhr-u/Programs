#include<stdio.h>
int main(){
  int max=-1000000000,tmp=-1000000000,min=1000000000,n,i,j=0,a[200000],prof[100000];
    
  scanf("%d",&n);
    
  for(i=0;i<n;i++){
    scanf("%d",&a[i]);
  }
    
  if(n==2){
       
    prof[0]=a[1]-a[0];
    j++;
        
  }else{
        
    for(i=0;i<n;i++){
        
      if(a[i]>max){
	max=a[i];
      }
        
      if(a[i]<min){
            
	prof[j]=max-min;
	j++;
	min=a[i];
	max=-1000000000;
      }
    }
    
    prof[j]=max-min;
    j++;
  }
    
  for(i=0;i<j;i++){
    if(prof[i]>tmp)tmp=prof[i];
  }
  printf("%d\n",tmp);
    
}
