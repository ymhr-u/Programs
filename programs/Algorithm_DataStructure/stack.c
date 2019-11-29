#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void push(int x);
int pop();

int top=0,S[1000];

int main(){
  int a,b,top=0;
  char s[100];

  while(scanf("%s",s)!=EOF){
    if(s[0]=='+'){
      a=pop();
      b=pop();
      push(a+b);
    }else if(s[0]=='-'){
      a=pop();
      b=pop();
      push(b-a);
    }else if(s[0]=='*'){
      a=pop();
      b=pop();
      push(a*b);
    }else{
      push(atoi(s));
    }
  }
  printf("%d\n",pop());
  return 0;
}

void push(int x){
  S[++top]=x;
}
int pop(){
  top--;
  return S[top+1];
}
