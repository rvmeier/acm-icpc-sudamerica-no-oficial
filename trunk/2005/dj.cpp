/*
 * ACM ICPC 2005 - Problem G "Computer DJ"
 * Author: Abraham M. Santos R. (amsantosr@gmail.com)
 */

#include <iostream>
#include <string>

using namespace std;

int table[27][32];

void make_table() {
   for ( int i = 2; i <= 26; i++ ) {
      table[i][0] = 0;
      int ipown= 1;
      for ( int j = 1; ; j++ ) {
         ipown *= i;
         table[i][j] = table[i][j-1] + ipown*j;
         if ( table[i][j] > 100000000 )
            break;
      }
   }
}

int get_digit(int n, int pos, int base) {
   for ( int i = 0; i < pos; i++ )
      n /= base;
   return n % base;
}

int get_pos(int N, int k) {
   if ( N == 1 ) return 0;
   int level = 0;
   while ( k > table[N][level] ) ++level;
   int line = k - table[N][level-1] - 1;
   int perm = line / level;
   int off = line % level;
   int pos = get_digit(perm, level-off-1, N);
   return pos;
}

int main() {
   int N, Q, k;
   make_table();
   string songs[26];
   while ( cin >> N >> Q, N != 0 || Q != 0 ) {
      for ( int i = 0; i < N; i++ )
         cin >> songs[i];
      for ( int i = 0; i < Q; i++ ) {
         cin >> k;
         int idx = get_pos(N, k);
         cout << songs[idx] << '\n';
      }
      cout << '\n';
   }
   return 0;
}
