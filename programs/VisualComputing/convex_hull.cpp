#include <vector>  
#include <iostream>  
using namespace std;  
  
// Global Vars and Structs  
struct Point {  
  int x;  
  int y;  
};  
int MaxPts;  
  
// Function prototypes  
int CrossProd(const Point Orig, const Point A, const Point B);  
vector<Point> convexHull(vector<Point> P);  
void Sort (Point P[]);  

int main()  {  
  // Input Data  
  cin >> MaxPts;  
  Point PointArray[MaxPts];  
  for (int i = 0; i < MaxPts; i++) {  
    cin >> PointArray[i].x;  
    cin >> PointArray[i].y;  
  }  
  
  // Sort  
  Sort(PointArray);  
  
  // Convert to Vector  
  vector<Point> PointVect(PointArray, PointArray+MaxPts);  
  
  // Calculate Hull  
  vector<Point> OutVect = convexHull(PointVect);  
  
  // Output  
  cout << endl << endl << "The points of the convex hull are:" << endl;  
  for (vector<Point>::iterator iter = OutVect.begin(); iter != OutVect.end();iter++) {  
    cout << "(" << iter->x << ", " << iter->y << ")" << endl;  
  }  
}  
  
vector<Point> convexHull(const vector<Point> &P){  
  
  int W = P.size(), Z = 0;  
  vector<Point> H(MaxPts * 2);  
  
  //lower
  for (int i = 0; i < W; i++) {  
    while (Z >= 2 && CrossProd(H[Z-2], H[Z-1], P[i]) <= 0){Z--;}
    H[Z++] = P[i];  
  }  
  
  //upper
  for (int i = W-2, t = Z+1; i >= 0; i--) {  
    while (Z >= t && CrossProd(H[Z-2], H[Z-1], P[i]) <= 0){Z--;}
    H[Z++] = P[i];  
  }  
  
  H.resize(Z);  
  H.erase(H.begin());  
  return H;  
}  
  
int CrossProd(const Point &Orig, const Point &A, const Point &B)  {  
  return (A.x - Orig.x) * (B.y - Orig.y) - (A.y - Orig.y) * (B.x - Orig.x);  
}  
  
void Sort (Point P[])  {  
  for( int i=0; i<MaxPts-1; i++ ) {  
    for( int j=1; j<MaxPts; j++) {  
  
      if( P[j].x < P[j-1].x ) {  
	temp=P[j];  
	P[j]=P[j-1];  
	P[j-1]=temp;  
      }  
  
      else if( P[j].x == P[j-1].x ) {  
	if( P[j].y < P[j-1].y ) {  
	  temp=P[j];  
	  P[j]=P[j-1];  
	  P[j-1]=temp;  
	}  
      }  
    }  
  }  
}  
