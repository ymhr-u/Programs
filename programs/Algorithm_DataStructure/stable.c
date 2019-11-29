#include <stdio.h>

typedef struct{
  char c;
  int number;
}Card;

int main(){
  char dm;
  int n,i,j,min,flag;
  Card a[36],b[36],x;
  scanf("%d\n",&n);
  for(i=0;i<n;i++){
    scanf("%c%d%c",&a[i].c,&a[i].number,&dm);
    b[i]=a[i];
  }

  for(i=0;i<n;i++){
    flag=0;
    for(j=n-1;j>i;j--){
      if(a[j].number<a[j-1].number){
        x=a[j];
        a[j]=a[j-1];
        a[j-1]=x;
        flag=1;
      }
    }
    if(flag==0)break;
  }

  for(i=0;i<n;i++){
    min=i;
    for(j=i;j<n;j++){
      if(b[j].number<b[min].number){min=j;}
    }

    if(min!=i){
      x=b[i];
      b[i]=b[min];
      b[min]=x;
    }
  }

  for(i=0;i<n-1;i++) printf("%c%d ",a[i].c,a[i].number);
  printf("%c%d\n",a[n-1].c,a[n-1].number);
  printf("Stable\n");
  for(i=0;i<n-1;i++) {printf("%c%d ",b[i].c,b[i].number);
    if(a[i].c!=b[i].c)flag=2;
  }
  printf("%c%d\n",b[n-1].c,b[n-1].number);
  if(flag==2)printf("Not stable\n");
  else printf("Stable\n");

  return 0;
}
