// best-Fit algorithm in c++

void bestFit(int blockSize[], int m, int processSize[], int n) { 

  int alloc[n]; 
  memset(alloc, -1, sizeof(alloc)); 
  
  for (int i=0;i<n;i++){ 
    int bestIdx = -1; 
    
    for (int j=0; j<m; j++){ 
      if (blockSize[j] >= processSize[i]) { 
	if (bestIdx == -1){bestIdx = j;}
	else if (blockSize[bestIdx] > blockSize[j]){bestIdx = j;} 
      } 
    } 
    
    // If we could find a block for current process 
    if (bestIdx != -1) { 
    
      // allocate block j to p[i] process 
      alloc[i] = bestIdx; 
      
      // Reduce available memory in this block. 
      blockSize[bestIdx] -= processSize[i]; 
    } 
  } 
  
  cout << "Process No.\tProcess Size\tBlock no.\n"; 
  for (int i=0; i<n; i++) { 
    cout << "   " << i+1 << "\t\t" << processSize[i] << "\t\t"; 
    if (alloc[i] != -1) {cout << alloc[i] + 1;}
    else{cout << "Not Allocated"; }
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
