/*
 * ACM ICPC 2005 - Problem F "Where Are My Genes"
 * Author: Abraham M. Santos R. (amsantosr@gmail.com)
 */

#include <iostream>

using namespace std;

int main() {
   int ngenes;
   int ngen = 0;
   while ( cin >> ngenes, ngenes != 0 ) {
      int revi[1000], revj[1000];
      int nrevs, nqueries;
      cin >> nrevs;
      for ( int i = 0; i < nrevs; i++ )
         cin >> revi[i] >> revj[i];
      cin >> nqueries;

      cout << "Genome " << ++ngen << '\n';
      for ( int i = 0; i < nqueries; i++ ) {
         int query;
         cin >> query;
         for ( int i = 0; i < nrevs; i++ ) {
            if ( revi[i] <= query && query <= revj[i] )
               query = revi[i] + revj[i] - query;
         }
         cout << query << '\n';
      }
   }
   return 0;
}x
