// C++ implementation of the approach 
#include <bits/stdc++.h> 
using namespace std; 
  

bool findQueue(queue<int> q, int x) { 
  while (!q.empty()) { 
    if (x == q.front()){return true;}
    q.pop(); 
  } 
  
  return false; 
} 


void LRU_Approximation(vector<int> t, int capacity) { 
  int n = t.size(); 
  queue<int> q; 
  
  int hits = 0, faults = 0, ptr = 0; 
  bool bitref[capacity] = { false }; 
  
  int count = 0; 
  for (int i = 0; i < t.size(); i++) { 
    if (!findQueue(q, t[i])) { 
      
      // Queue is not filled up to capacity 
      if (count < capacity) { 
	q.push(t[i]); 
	count++; 
      } 
      
      // Queue is filled up to capacity 
      else { 
	ptr = 0; 
	
	// Find the first value that has its bit set to 0 
	while (!q.empty()) { 
	  
	  if (bitref[ptr % capacity]) {
	    bitref[ptr % capacity] = !bitref[ptr % capacity]; 
	  }
	  else{
	    break;
	  }
	  
	  ptr++; 
	} 
	
	// If the queue was empty 
	if (q.empty()) { 
	  q.pop(); 
	  q.push(t[i]); 
	} 
	
	// If queue was not empty 
	else { 
	  int j = 0; 
	  while (j < (ptr % capacity)) { 
	    int t1 = q.front(); 
	    q.pop(); 
	    q.push(t1); 
	    bool temp = bitref[0]; 
	    
	    // Rotate the bitref array 
	    for (int counter = 0; counter < capacity - 1; counter++) 
	      bitref[counter] = bitref[counter + 1]; 
	    bitref[capacity - 1] = temp; 
	    j++; 
	  } 
	  
	  q.pop(); 
	  q.push(t[i]); 
	} 
      } 
      faults++; 
    } 
    
    // If the input for the iteration was a hit 
    else { 
      queue<int> temp = q; 
      int counter = 0; 
      while (!q.empty()) { 
	if (q.front() == t[i]) 
	  bitref[counter] = true; 
	counter++; 
	q.pop(); 
      } 
      q = temp; 
      hits++; 
    } 
  } 
  
  cout << "Hits: " << hits << "\nFaults: " << faults << '\n'; 
} 


int main() { 
  vector<int> t = { 2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5, 2 }; 
  int capacity = 4; 
  LRU_Approximation(t, capacity); 
  
  return 0; 
} 
