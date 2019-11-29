// C++ implementation of worst - Fit algorithm 
#include<bits/stdc++.h> 
using namespace std; 
  
void worstFit(int blockSize[], int m, int processSize[],int n){

  int alloc[n]; 
  memset(alloc, -1, sizeof(alloc)); 
  
  for (int i=0; i<n; i++){ 
    
    int wstIdx = -1; 
    for (int j=0; j<m; j++) {
      if (blockSize[j] >= processSize[i]){ 
	if (wstIdx == -1) 
	  wstIdx = j; 
	else if (blockSize[wstIdx] < blockSize[j]) 
	  wstIdx = j; 
      } 
    } 
    
    // If we could find a block for current process 
    if (wstIdx != -1) { 
  
      // allocate block j to p[i] process 
      alloc[i] = wstIdx; 
      
      // Reduce available memory in this block. 
      blockSize[wstIdx] -= processSize[i]; 
    } 
  } 
  
  cout << "Process No.\tProcess Size\tBlock no.\n"; 
  for (int i = 0; i < n; i++){ 
    cout << "   " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
    if (alloc[i] != -1) {cout << alloc[i] + 1; }
    else {cout << "Not Allocated"; }
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
