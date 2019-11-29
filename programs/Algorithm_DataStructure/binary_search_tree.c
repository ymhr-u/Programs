#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
  int key;
  struct Node *right,*left,*parent;
};

struct Node *root,*NIL;

void insert(int k){
  struct Node *y=NIL;
  struct Node *x=root;
  struct Node *z;
  z=malloc(sizeof(struct Node));
  z->key=k;
  z->left=NIL;
  z->right=NIL;
  while(x!=NIL){
    y=x;
    if(z->key < x->key){x=x->left;}
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
  int n,i,x;
  char *str1="insert";
  char *str2="print";
  char tmp[1000];

  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%s",tmp);
    if(strcmp(tmp,str1)==0){
      scanf("%d",&x);
      insert(x);
    }
    else if(strcmp(tmp,str2)==0){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
  }
  return 0;
}
