/*
 * ACM ICPC 2008 Problem B: Bases
 * Author: Abraham M. Santos Ramos
 *
 * Each expression is transformed into a polynomial of variable b (base)
 * to find the bases allowed. Taken submultiples of the last number
 * in the polynomial and using Horner method we found bases.
 * Bases must be greater than the highest digit in both expressions.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <functional>
#include <cassert>

#define NDEBUG
using namespace std;
vector<int> P;

void mkprimes(int lim) {
   P.push_back(2);
   for ( int i = 3; i <= lim; i += 2 ) {
      for ( int j = 0; P[j]*P[j] <= i; j++ )
         if ( i % P[j] == 0 )
            goto NOPRIME;
      //cout << i << '\n';
      P.push_back(i);
NOPRIME:
      ;
   }
}

template<typename Op>
vector<int> poly_add(const vector<int> &a, const vector<int> &b, Op op) {
   int asz = (int)a.size();
   int bsz = (int)b.size();
   int sz = max(asz, bsz);
   vector<int> s(sz, 0);
   for ( int i = 0; i < sz; i++ )
      s[i] = op(i < asz ? a[i] : 0, i < bsz ? b[i] : 0);
   while ( sz > 1 && s.back() == 0 )
      s.pop_back(), --sz;
   return s;
}

vector<int> poly_mult(const vector<int> &a, const vector<int> &b) {
   static const vector<int> zero(1, 0);
   if ( a == zero || b == zero ) return zero;
   //assert(a.back() != 0 && b.back() != 0);
   int asz = (int)a.size();
   int bsz = (int)b.size();
   vector<int> p(asz+bsz-1, 0);
   for ( int i = 0; i < asz; i++ )
      for ( int j = 0; j < bsz; j++ )
         p[i+j] += a[i] * b[j];
   assert(p.back() != 0);
   return p;
}

vector<int> expr(const string &s) {
   vector<int> v1, v2, v3;
   int i = (int)s.size();

   for ( --i; i >= 0 && isdigit(s[i]); i-- )
      v2.push_back(s[i]-'0');
   while ( i >= 0 ) {
      char op = s[i];
      v3.clear();
      for ( --i; i >= 0 && isdigit(s[i]); i-- )
         v3.push_back(s[i]-'0');
      if ( op == '*' )
         v2 = poly_mult(v2, v3);
      else {
         v1 = poly_add(v1, v2, plus<int>());
         v2 = v3;
      }
   }
   v1 = poly_add(v1, v2, plus<int>());
   return v1;
}

// for debugging
void wrpoly(const vector<int> &v) {
   int sz = (int)v.size();
   cout << '[' << v[0];
   for ( int i = 1; i < sz; i++ )
      cout << ',' << v[i];
   cout << ']';
}

void factorize(const vector< pair<int,int> > &f, int i, vector<int> &s, int val) {
   if ( i == (int)f.size() ) {
      s.push_back(val);
      return;
   }
   int px = 1;
   for ( int j = 0; j <= f[i].second; j++ ) {
      factorize(f, i+1, s, val*px);
      px *= f[i].first;
   }
}

vector<int> submultiples(int x) {
   vector< pair<int, int> > f;
   for ( int i = 0; P[i]*P[i] <= x; i++ )
      if ( x % P[i] == 0 ) {
         f.push_back(make_pair(P[i], 0));
         while ( x % P[i] == 0 ) {
            x /= P[i];
            f.back().second++;
         }
      }
   if ( x != 1 )
      f.push_back(make_pair(x, 1));
   vector<int> s;
   factorize(f, 0, s, 1);
   sort(s.begin(), s.end());
   return s;
}

// modified version to lead with integer overflow
int horner(const vector<int> &p, int x) {
   int sz = (int)p.size();
   int sum = 0;
   const int imax = INT_MAX;
   for ( int i = sz-1; i >= 0; i-- ) {
      if ( imax/x < sum ) return 1;
      sum *= x;
      if ( p[i] > 0 && imax-p[i] < sum ) return 1;
      sum += p[i];
   }
   return sum;
}

void roots(vector<int> p, int c) {
   int sz = (int)p.size();
   c = max(c, 1);
   while ( sz > 1 && p[0] == 0 ) {
      p.erase(p.begin());
      --sz;
   }
   if ( sz == 1 ) {
      if ( p[0] == 0 ) cout << c+1 << '+';
      else cout << '*';
      cout << '\n';
      return;
   }

   //vector<int> r;
   vector<int> sm = submultiples(p[0] > 0 ? p[0] : -p[0]);
   //cout << "sm = "; wrpoly(sm); cout << '\n';
   int ssz = (int)sm.size();
   bool st = true;
   for ( int i = 0; i < ssz; i++ )
      if ( sm[i] > c && horner(p, sm[i]) == 0 ) {
         //p = ruffini(p, sm[i]);
         if ( st ) st = false;
         else cout << ' ';
         cout << sm[i];
      }
   if ( st ) cout << '*';
   cout << '\n';
}

int main() {
   string s;
   mkprimes(19683);
   while ( getline(cin, s), s[0] != '=' ) {
      string::size_type pos = s.find('=');
      vector<int> v1 = expr(s.substr(0, pos));
      vector<int> v2 = expr(s.substr(pos+1));
      /*cout << "v1 = "; wrpoly(v1); cout << '\n';
      cout << "v2 = "; wrpoly(v2); cout << '\n';*/
      v1 = poly_add(v1, v2, minus<int>());
      //cout << "p = "; wrpoly(v1); cout << '\n';
      int sz = (int)s.size();
      char ch = '0';
      for ( int i = 0; i < sz; i++ )
         if ( isdigit(s[i]) )
            ch = max(ch, s[i]);
      roots(v1, ch-'0');
   }
   return 0;
}
