#include <stdio.h>
#define NIL -1

typedef struct{
  int p;
  int l;
  int r;
} Node;

Node T[10000];
int n;

void pre(int u){
  if(u==NIL) return;
  printf(" %d",u);
  pre(T[u].l);
  pre(T[u].r);
}
void in(int u){
  if(u==NIL) return;
  in(T[u].l);
  printf(" %d",u);
  in(T[u].r);
}
void post(int u){
  if(u==NIL) return;
  post(T[u].l);
  post(T[u].r);
  printf(" %d",u);
}

int main(){
  int i,v1,v2,v3,root;
  scanf("%d",&n);
  for(i=0;i<n;i++){T[i].p=NIL;}

  for(i=0;i<n;i++){
    scanf("%d %d %d",&v1,&v2,&v3);
    T[v1].l=v2;
    T[v1].r=v3;
    if(v2!=NIL){T[v2].p=v1;}
    if(v3!=NIL){T[v3].p=v1;}
  }

  for(i=0;i<n;i++) if(T[i].p==NIL) root=i;
  printf("Preorder\n");
  pre(root);
  printf("\n");
  printf("Inorder\n");
  in(root);
  printf("\n");
  printf("Postorder\n");
  post(root);
  printf("\n");
  return 0;
}
