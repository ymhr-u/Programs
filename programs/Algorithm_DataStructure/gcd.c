#include <stdio.h>
void insertion(int a,int b);

int main(int argc, const char * argv[]) {
  int a,b;
  scanf("%d %d",&a,&b);
  printf("%d\n",gcd(a,b));
}

int gcd(int a,int b){
  int r;
  while((r = a % b) != 0){
    a = b;
    b = r;
  }
  return b;
}
