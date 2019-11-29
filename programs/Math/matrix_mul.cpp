#include <iostream>
 
int main(void){
 
  int i, j, k, term;
  int a[2][2], b[2][3], c[2][3];
 
  std::cout<<"input first matrix"<<std::endl;
  for(i=0;i<2;++i){
    for(j=0;j<2;++j){
      std::cout << "a["<< i+1 <<"]["<< j+1<<"] = "<<std::endl;
      std::cin>>a[i][j];
    }
  }
  
  std::cout <<"\n2つ目の行列 B を入力\n"<<std::endl;
  for(i=0;i<2;++i){
    for(j=0;j<3;++j){
      std::cout << "b["<< i+1 <<"]["<< j+1<<"] = "<<std::endl;
      std::cin>>b[i][j];
    }
  }
 
  /* 行列の積（掛け算） */
  for(i=0;i<2;++i){
    for(j=0;j<3;++j){
      c[i][j] = a[i][j] * b[i][j];
 
      // 行列の項を計算
      for(i=0;i<2;i++){
        for(j=0;j<3;j++){
          term = 0;
          for(k=0;k<2;k++)
            term = term + a[i][k]*b[k][j];
          c[i][j] = term;
        }
      }
 
    }
  }
 
  printf("\n行列 C = A x B\n");
  for(i=0;i<2;++i){
    for(j=0;j<3;++j){
      printf("C[%d][%d] = %d\n", i+1, j+1, c[i][j]);
    }
  }
 
  return 0;
}
