#include <stdio.h>
void mergesort(int* A,int left,int right);
void merge(int* A,int left,int mid,int right);

int c=0;

int main(){
  int n,a[500000],i,mid;
  scanf("%d",&n);
  for(i=0;i<n;i++){scanf("%d",&a[i]);}

  mid=n/2;
  mergesort(a,0,n);

  for(i=0;i<n-1;i++){printf("%d ",a[i]);}
  printf("%d\n%d\n",a[n-1],c);
  return 0;
}

void mergesort(int A[], int left,int right){
  int mid;
  if (left+1 < right){
    mid = (left + right)/2;
    mergesort(A, left, mid);
    mergesort(A, mid, right);
    merge(A, left, mid, right);
  }
}

void merge(int A[],int left,int mid,int right){
  int i,j,k,n1,n2,LeftArr[500000],RightArr[500000];

  n1 = mid - left;
  n2 = right - mid;

  for (i = 0; i<n1;i++){LeftArr[i] = A[left + i];}
  for (i = 0; i<n2;i++){RightArr[i] = A[mid + i];}
  LeftArr[n1] = 1000000001;
  RightArr[n2] = 1000000001;

  i = 0;
  j = 0;

  for (k = left; k<right; k++){
    if (LeftArr[i] <= RightArr[j]){
      A[k] = LeftArr[i];
      i+=1;
      c++;
    }
    else {
      A[k] = RightArr[j];
      j+=1;
      c++;
    }
  }
}
