#include<stdio.h>
#include<string.h>
#define N 100000

struct P{
  char name[100];
  int num;
};

int head, tail, n, c=0, q;
struct P Q[N];
void enqueue(){

  Q[head].num=(Q[head].num)-q;
  Q[tail] = Q[head];

  if(tail > n+1){tail = 0;}
  else tail++;
}

void dequeue(){
  printf("%s %d\n",Q[head].name, Q[head].num+c);
}

int main(){
  int i;

  scanf("%d %d", &n, &q);
  for ( i = 1; i <= n; i++){
    scanf("%s", Q[i].name);
    scanf("%d", &Q[i].num);
  }
  head = 1;
  tail = n+1;
  i = 1;

  while(head != tail){
    if(Q[head].num > q){
      enqueue();
      c+=q;
    }
    else{
      dequeue();
      c+=Q[head].num;
    }
    if(head>n+1){head = 0;}
    else head++;
  }
  return 0;
}
