/*
 * ACM ICPC 2005 - Problem C "Pascal Library"
 * Author: Abraham M. Santos R. (amsantosr@gmail.com)
 */

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
   int N, D;
   bool alumni[100];
   while ( cin >> N >> D, N != 0 || D != 0 ) {
      fill_n(alumni, N, true);
      int count = N;
      for ( int i = 0; i < D; i++ ) {
         for ( int j = 0; j < N; j++ ) {
             int attend;
             cin >> attend;
             if ( !attend && alumni[j] ) {
                alumni[j] = false;
                --count;
             }
         }
      }
      cout << (count ? "yes" : "no") << '\n';
   }
   return 0;
}
