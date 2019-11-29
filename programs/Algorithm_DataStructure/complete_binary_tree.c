#include <stdio.h>
#define MAX 251
int parent(int i) {return i/2;}
int left(int i) {return 2*i;}
int right(int i) {return 2*i+1;}

int main()
{
  int h,i,a[MAX+1];
  scanf("%d",&h);
  for(i=1;i<=h;i++) scanf("%d",&a[i]);
  for(i=1;i<=h;i++){
    printf("node %d: key = %d, ",i,a[i]);
    if(parent(i)>=1) printf("parent key = %d, ",a[parent(i)]);
    if(left(i)<=h) printf("left key = %d, ",a[left(i)]);
    if(right(i)<=h) printf("right key = %d, ",a[right(i)]);
    printf("\n");
  }


  return 0;
}
