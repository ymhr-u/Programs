#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
  int key;
  struct Node *right,*left,*parent;
};

struct Node *root,*NIL;

//add this function
struct Node *find(struct Node *u,int k){
  while(u!=NIL && k!=u->key){
    if(k < u->key) u=u->left;
    else u=u->right;
  }
  return u;
}

void insert(int k){
  struct Node *y=NIL;
  struct Node *x=root;
  struct Node *z;
  z=(struct Node *)malloc(sizeof(struct Node));
  z->key=k;
  z->left=NIL;
  z->right=NIL;
  while(x!=NIL){
    y=x;
    if(z->key < x->key) x=x->left;
    else x=x->right;
  }
  z->parent=y;
  if(y==NIL) root=z;
  else {
    if(z->key < y->key) y->left=z;
    else y->right=z;
  }
}

void inorder(struct Node *u){
  if(u==NIL) return;
  inorder(u->left);
  printf(" %d",u->key);
  inorder(u->right);
}

void preorder(struct Node *u){
  if(u==NIL) return;
  printf(" %d",u->key);
  preorder(u->left);
  preorder(u->right);
}

int main(){
  struct Node *t;
  int n,i,x;
  char tmp[1000];

  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%s",tmp);
    if(strcmp(tmp,"find")==0){
      scanf("%d",&x);
      t=find(root,x);
      if(t!=NIL) printf("yes\n");
      else printf("no\n");
    }
    else if(strcmp(tmp,"insert")==0){
      scanf("%d",&x);
      insert(x);
    }
    else if(strcmp(tmp,"print")==0){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
  }
  return 0;
}
