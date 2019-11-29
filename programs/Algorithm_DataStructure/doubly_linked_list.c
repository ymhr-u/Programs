#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
  int key;
  struct Node *next,*prev;
};
struct Node *nil;
struct Node *listSearch(int key){
  struct Node *cur = nil->next;
  while(cur!=nil && cur->key!=key){cur=cur->next;}
  return cur;
}

void init(){
  nil=(struct Node *)malloc(sizeof(struct Node));
  nil->next=nil;
  nil->prev=nil;
}

void printList(){
  struct Node *cur=nil->next;
  int i=0;
  while(1){
    if(cur==nil) break;
    if(i++>0) printf(" ");
    printf("%d",cur->key);
    cur=cur->next;
  }
  printf("\n");
}

void deleteNode(struct Node *t){
  if(t==nil) return;
  t->prev->next=t->next;
  t->next->prev=t->prev;
  free(t);
}

void deleteFirst(){
  deleteNode(nil->next);
}

void deleteLast(){
  deleteNode(nil->prev);
}

void deleteKey(int key){
  deleteNode(listSearch(key));
}

void insert(int key){
  struct Node *x=(struct Node *)malloc(sizeof(struct Node));
  x->key=key;
  x->next=nil->next;
  nil->next->prev=x;
  nil->next=x;
  x->prev=nil;
}

int main(){
  int key,n,i,size=0,np=0,nd=0;;
  char ch[15];

  init();

  scanf("%d",&n);

  for(i=0;i<n;i++){
    scanf("%s %d",ch,&key);
    if(ch[0]=='i'){
      insert(key);
      np++;
      size++;
    }

    else if(ch[0]=='d'){
      if(strlen(ch)>6){
        if(ch[6]=='F') {deleteFirst();}
        else if(ch[6]=='L') {deleteLast();}
      }
      else {
        deleteKey(key);
        nd++;
      }
      size--;
    }
  }
  printList();
}
