// C/C++ program for next fit memory management algorithm 
#include <bits/stdc++.h> 
using namespace std; 
  
void NextFit(int blockSize[], int m, int processSize[], int n) { 

  int alloc[n], j = 0; 
  
  memset(alloc, -1, sizeof(alloc)); 
  
  for (int i=0; i<n; i++){ 
  
    //start from end 
    while (j < m) { 

      if (blockSize[j] >= processSize[i]) { 
	allocation[i] = j; 
	blockSize[j] -= processSize[i]; 
	break; 
      } 
      
      j = (j + 1) % m; 
    } 
  } 
  
  cout << "\nProcess No.\tProcess Size\tBlock no.\n"; 

  for (int i = 0; i < n; i++) { 
    cout << " " << i + 1 << "\t\t" << processSize[i] << "\t\t"; 
    if (alloc[i] != -1) {cout << alloc[i] + 1;} 
    else{cout << "Not Allocated";} 
    cout << endl; 
  } 

} 

int main()
{
  int blockSize[] = {500, 100, 250, 600, 300};
  int processSize[] = {412, 117, 117, 466};
  int m = sizeof(blockSize) / sizeof(blockSize[0]);
  int n = sizeof(processSize) / sizeof(processSize[0]);

  firstFit(blockSize, m, processSize, n);

  return 0 ;
}
