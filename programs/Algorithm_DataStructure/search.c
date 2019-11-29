#include<stdio.h>
#include<string.h>
#define M 1000000
#define L 12
#define NIL -1

char A[M][L];

int getChar(char c){
  if(c == 'A') return 1;
  else if(c == 'C') return 2;
  else if(c == 'G') return 3;
  else if(c == 'T') return 4;
}

int getKey(char str[]){
  int sum=0,p=1,i;
  for(i=0;i<strlen(str);i++){
    sum+=p*(getChar(str[i]));
    p*=5;
  }
  return sum;
}

int h1(int key){return key % M;}
int h2(int key){return 1 + (key%(M-1));}

int find(char str[]){
  int i,h,key;
  key = getKey(str);

  for(i=0;;i++){
    h = (h1(key) + i*h2(key)) % M;
    if(strcmp(A[h],str) == 0) return 1;
    else if(strlen(A[h]) == 0) return 0;
  }
  return 0;
}

int insert(char str[]){
  long long key,i,h;
  key = getKey(str);
  for(i=0 ; ; i++){
    h = (h1(key) + i*h2(key)) % M;
    if(strcmp(A[h],str) == 0) return 1;
    else if(strlen(A[h]) == 0){
      strcpy(A[h], str);
      return 0;
    }
  }
  return 0;
}

int main(){
  int i,n,h;
  char str[L], ch[9];

  scanf("%d", &n);
  for (i=0 ; i<n ; i++){A[i][0]='\0';}
  for (i=0 ; i<n ; i++){
    scanf("%s %s",ch,str);
    if (ch[0] == 'i'){insert(str);}
    else {
      if(find(str)){printf("yes\n");}
      else {printf("no\n");}
    }
  }
  return 0;
}
