#include<stdio.h>
#define MAX 100000
#define NIL -1
void depth(int a, int i);
void print(int a,int i);

int parent[MAX],left[MAX],right[MAX],D[MAX];

int main(){
  int i,j,n1,n2,le,ri,c,a,b;

  scanf("%d",&n1);
  for(i=0;i<n1;i++){parent[i]=left[i]=right[i]=NIL;}

  for(i=0;i<n1;i++){
    scanf("%d%d",&a,&n2);
    for(j=0;j<n2;j++){
      scanf("%d",&c);
      if(j==0){left[a]=c;}
      else{right[le]=c;}
      le=c;
      parent[c]=a;
    }
  }
  for(i=0;i<n1;i++){if(parent[i]==NIL)ri=i;}

  depth(ri,0);
  for(i=0;i<n1;i++){print(i,n1);}

  return 0;
}

void print(int a,int n){
  int i,b;
  printf("node %d: ",a);
  printf("parent = %d, ",parent[a]);
  printf("depth = %d, ",D[a]);
  if(parent[a] == NIL) printf("root, ");
  else if(left[a] == NIL) printf("leaf, ");
  else printf("internal node, ");
  printf("[");
  for(i=0,b=left[a];b!=NIL;i++,b=right[b]){
    if(i != 0) printf(", ");
    printf("%d",b);
  }

  printf("]\n");
}

void depth(int a, int i){
  D[a] = i;
  if(right[a] != NIL) depth(right[a],i);
  if(left[a] != NIL) depth(left[a],i+1);
}
