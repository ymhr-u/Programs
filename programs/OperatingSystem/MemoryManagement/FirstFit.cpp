// C++ implementation of First - Fit algorithm 
#include<bits/stdc++.h> 
using namespace std; 
  
void firstFit(int blockSize[],int m,int processSize[], int n) { 
    
  int alloc[n]; 
  
  // Initially no block is assigned to any process 
  memset(alloc, -1, sizeof(alloc)); 
  
 
  for (int i = 0; i<n; i++) { 
    for(int j = 0; j<m; j++){ 
      if (blockSize[j] >= processSize[i]){ 
	
	// allocate block j to p[i] process 
	alloc[i] = j; 
	
	// Reduce available memory in this block. 
	blockSize[j] -= processSize[i];  
	break; 
      } 
    } 
  } 
  
  cout << "Process No.\tProcess Size\tBlock no.\n"; 
  for (int i=0; i<n; i++) { 
    cout << " " << i+1 << "\t\t"<< processSize[i] << "\t\t"; 
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
