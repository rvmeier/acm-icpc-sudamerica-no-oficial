/*
 * ACM ICPC 2005 - Problem H "P-Networks"
 * Author: Abraham M. Santos R. (amsantosr@gmail.com)
 */

#include <iostream>
#include <algorithm>

using namespace std;

int N; // transformation size
int NS; // p-network length (num of strokes)
int T[20]; // the transformation array
int P[190]; // the p-network

// returns true if the p-network can be built and built it.
// otherwise returns false.
bool build_pnet() {
   int F = 0;
   // check that every number doesn't repeat.
   // using bits for efficiency
   for ( int i = 0; i < N; i++ ) {
      if ( F & (1<<T[i]) )
         return false;
      F |= (1<<T[i]);
   }

   // build the p-network using bubble sort
   // storing each exchange
   NS = 0;
   for ( int i = 0; i < N; i++ )
      for ( int j = N-1; j > i; j-- )
         if ( T[j] < T[j-1] ) {
            swap(T[j], T[j-1]);
            P[NS++] = j;
         }
   return true;
}

int main() {
   while ( cin >> N, N ) {
      // read the transformation
      for ( int i = 0; i < N; i++ )
         cin >> T[i];
      if ( !build_pnet() )
         cout << "No solution";
      else {
         // print the p-network
         cout << NS;
         for ( int i = 0; i < NS; i++ )
            cout << ' ' << P[i];
      }
      cout << '\n';
   }
   return 0;
}
