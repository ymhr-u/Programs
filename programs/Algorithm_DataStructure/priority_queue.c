#define MAX 2000000
#define INF 99999999
int h,A[MAX+1];

void maxHeapify(int i){
  int tmp,largest,l,r;

  l=2*i;
  r=2*i+1;

  if(l<=h && A[l]>A[i]) largest=l;
  else largest=i;
  if(r<=h && A[r]>A[largest]) largest=r;
  if(largest!=i){
    tmp=A[i];
    A[i]=A[largest];
    A[largest]=tmp;
    maxHeapify(largest);
  }
}

int extractmax(){
  int max_v;
  if(h<1) return -INF;
  max_v=A[1];
  A[1]=A[h--];
  maxHeapify(1);
  return max_v;
}

void increaseKey(int i,int key){
  int tmp;
  if(key<A[i]) return;
  A[i]=key;
  while(i>1 && A[i/2]<A[i]){
    tmp=A[i];
    A[i]=A[i/2];
    A[i/2]=tmp;
    i/=2;
  }
}

void insert(int key){
  h++;
  A[h]=-INF;
  increaseKey(h,key);
}

int main(){
  int key;
  char ch[7];
  while(1){
    scanf("%s",ch);
    if(ch[0]=='e' && ch[1]=='n'){break;}
    if(ch[0]=='i'){
      scanf("%d",&key);
      insert(key);
    }
    else printf("%d\n",extractmax());
  }
  return 0;
}