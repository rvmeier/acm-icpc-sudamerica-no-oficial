/*
 * ACM ICPC 2005 - Problem A "Tornado!"
 * Author: Abraham M. Santos R. (amsantosr@gmail.com)
 */

#include <iostream>

using namespace std;

int main() {
   int N;
   while ( cin >> N, N != 0 ) {
      int count = 0;
      int last = 0;
      int first = 1;
      bool start = true;

      for ( int i = 0; i != N; i++ ) {
         bool good;
         cin >> good;
         if ( good ) {
            if ( start ) {
               start = false;
               first = last;
            }
            last = 0;
         } else if ( ++last == 2 ) {
            ++count;
            last = 0;
         }
      }
      if ( first == 1 && last == 1 )
         ++count;
      cout << count << '\n';
   }
   return 0;
}
