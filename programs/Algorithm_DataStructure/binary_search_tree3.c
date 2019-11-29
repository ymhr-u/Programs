#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
  int key;
  struct Node *right,*left,*parent;
};

typedef struct Node Node;
Node *root,*NIL;

Node *find(Node *x,int k){
  while(x!=NIL && k!=x->key){
    if(k < x->key) x=x->left;
    else x=x->right;
  }
  return x;
}

Node *treeMinimum(Node *x){
  while(x->left!=NIL) x=x->left;
  return x;
}

Node *treeSuccessor(Node *x){
  if(x->right!=NIL){return treeMinimum(x->right);}
  Node *y=x->parent;
  while(y!=NIL && x==y->right ){
    x=y;
    y=y->parent;
  }
  return y;
}

void treeDelete(Node *x){
  Node *y,*z;
  if(x->left==NIL || x->right==NIL){y=x;}
  else {y=treeSuccessor(x);}
  if(y->left!=NIL) {z=y->left;}
  else {z=y->right;}

  if(z!=NIL){z->parent=y->parent;}
  if(y->parent==NIL){root=z;}
  else {
    if(y==y->parent->left){y->parent->left=z;}
    else{y->parent->right=z;}
  }

  if(y!=x) x->key=y->key;
  free(y);
}

void insert(int k){
  Node *y=NIL;
  Node *x=root;
  Node *z;
  z=(Node *)malloc(sizeof(Node));
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
  int i,n,x;
  char ch[100];
  char *pt="print";
  char *it="insert";
  char *dt="delete";
  Node *t;
  scanf("%d",&n);

  for(i=0;i<n;i++){
    scanf("%s",ch);
    if(ch[0]=='f'){
      scanf("%d",&x);
      t=find(root,x);
      if(t!=NIL) printf("yes\n");
      else printf("no\n");
    }
    else if(strcmp(ch,it)==0){
      scanf("%d",&x);
      insert(x);
    }
    else if(strcmp(ch,pt)==0){
      inorder(root);
      printf("\n");
      preorder(root);
      printf("\n");
    }
    else if(strcmp(ch,dt)==0){
      scanf("%d",&x);
      treeDelete(find(root,x));
    }
  }

  return 0;
}
