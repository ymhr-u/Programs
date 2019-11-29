#include<stdio.h>
void insertion(int *a,int n);

int main(){
  int i,n,m,a[100000],q,sum=0,left,right,mid;

  scanf("%d",&n);
  for(i=0;i<n;i++){scanf("%d",&a[i]);}
  insertion(&a,n);

  scanf("%d",&m);
  for(i=0;i<m;i++){
    scanf("%d",&q);
    left=0;
    right=n;
    while(left<right){
      mid=(left+right)/2;
      if(a[mid]==q){
	sum++;
	break;
      }
      else if(q<a[mid]) right=mid;
      else left=mid+1;
    }
  }
  printf("%d\n",sum);
  return 0;
}


void insertion(int *a,int n){
  int i,j,k,v;
  for(i=1;i<n;i++){
    v=a[i];
    j=i-1;
    while(j>=0 && a[j]>v){
      a[j+1]=a[j];
      j--;
    }
    a[j+1]=v;
  }
}
