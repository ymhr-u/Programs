#include <stdio.h>
#include <math.h>

typedef struct{
  double x;
  double y;
} Point;

void Koch(int n,Point a,Point b){
  if(n==0) return;
  Point s,t,u;
  double th=M_PI*60.0/180.0;

  s.x=(2.0*a.x+1.0*b.x)/3.0;
  s.y=(2.0*a.y+1.0*b.y)/3.0;
  t.x=(1.0*a.x+2.0*b.x)/3.0;
  t.y=(1.0*a.y+2.0*b.y)/3.0;
  u.x=(t.x-s.x)*cos(th)-(t.y-s.y)*sin(th)+s.x;
  u.y=(t.x-s.x)*sin(th)+(t.y-s.y)*cos(th)+s.y;

  Koch(n-1,a,s);
  printf("%.8f %.8f\n",s.x,s.y);
  Koch(n-1,s,u);
  printf("%.8f %.8f\n",u.x,u.y);
  Koch(n-1,u,t);
  printf("%.8f %.8f\n",t.x,t.y);
  Koch(n-1,t,b);
}

int main(){
  Point a,b;
  int n;
  scanf("%d",&n);
  a.x=a.y=b.y=0;
  b.x=100;
  printf("%.8f %.8f\n",a.x,a.y);
  Koch(n,a,b);
  printf("%.8f %.8f\n",b.x,b.y);

}
