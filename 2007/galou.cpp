/*
 * ACM ICPC 2007 - Problem G "Galou is back"
 * Author: Abraham M. Santos R. (amsantosr@gmail.com)
 */

#include <iostream>
#include <vector>

using namespace std;
typedef vector<int> IntVect;

int R, C;
char mat[100][100];
const int dr[6] = { -1, -1, 0, 0, 1, 1 };
const int dc[6] = { 0, 1, -1, 1, -1, 0 };

inline int mkcod(int r, int c) { return 100*r + c; }
inline int check(int r, int c)
{ return 0 <= r && r < R && 0 <= c && c < C; }

bool rotate(int r, int c)
{
   IntVect Q;
   IntVect P;
   Q.push_back(mkcod(r, c));
   char turn = '(';

   while ( !Q.empty() ) {
      do {
         r = Q.back() / 100;
         c = Q.back() % 100;
         Q.pop_back();
         mat[r][c] = turn;

         for ( int k = 0; k < 6; k++ ) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if ( check(nr, nc) ) {
               if ( mat[nr][nc] == 'I' ) {
                  mat[nr][nc] = '(';
                  P.push_back(mkcod(nr, nc));
               }
               if ( mat[nr][nc] == turn )
                  return false;
               if ( mat[nr][nc] == '*' )
                  P.push_back(mkcod(nr, nc));
            }
         }
      } while ( !Q.empty() );
      Q.swap(P);
      turn = (turn == '(' ? ')' : '(');
   }
   return true;
}

void paralyze(int r, int c)
{
   IntVect Q;
   Q.push_back(mkcod(r, c));

   while ( !Q.empty() ) {
      r = Q.back() / 100;
      c = Q.back() % 100;
      Q.pop_back();
      mat[r][c] = 'B';

      for ( int k = 0; k < 6; k++ ) {
         int nr = r + dr[k];
         int nc = c + dc[k];
         if ( check(nr, nc) && mat[nr][nc] != '.' )
            if ( mat[nr][nc] != 'B' )
               Q.push_back(mkcod(nr, nc));
      }
   }
}

int main()
{
   while ( cin >> R >> C, R || C ) {
      for ( int i = 0; i < R; i++ )
         for ( int j = 0; j < C; j++ )
            cin >> mat[i][j];

      for ( int i = 0; i < R; i++ )
         for ( int j = 0; j < C; j++ )
            if ( mat[i][j] == 'I' )
               if ( !rotate(i, j) )
                  paralyze(i, j);

      cout << '\n';
      for ( int i = 0; i < R; i++ ) {
         for ( int j = 0; j < C; j++ )
            cout << (mat[i][j] == '*' ? 'F' : mat[i][j]);
         cout << '\n';
      }
   }
   return 0;
}
