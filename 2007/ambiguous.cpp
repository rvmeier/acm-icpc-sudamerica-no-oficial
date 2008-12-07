/*
 * ACM ICPC 2007 South America Problem A: Ambiguous Codes.
 * Author: Abraham M. Santos R.
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
#include <algorithm>

#define Ptr first
#define Len second
#define Node first
#define Cost second

using namespace std;

typedef pair<const char*, int> Substr;
class SubRank {
public:
   bool operator()(const Substr &s1, const Substr &s2)
   { return s1.Len != s2.Len ? s1.Len < s2.Len
   : lexicographical_compare(s1.Ptr, s1.Ptr+s1.Len, s2.Ptr, s2.Ptr+s2.Len); }
};

typedef pair<Substr, int> Prefix;
class PrefRank {
public:
   bool operator()(const Prefix &p1, const Prefix &p2)
   { return p1.Cost > p2.Cost; }
};

int N;
char W[100][51];
int L[100];

int ambiguity() {
   map<Substr, int, SubRank> C;
   priority_queue<Prefix, vector<Prefix>, PrefRank> Q;

   for ( int j = 0; j < N; j++ )
      for ( int i = 0; i < j; i++ ) {
         const char *ptr1 = W[i];
         const char *ptr2 = W[j];
         int len1 = L[i], len2 = L[j];
         if ( len1 > len2 ) {
            swap(len1, len2);
            swap(ptr1, ptr2);
         }
         if ( equal(ptr1, ptr1+len1, ptr2) ) {
            Substr part(ptr2+len1, len2-len1);
            int &cost = C[part];
            if ( cost == 0 || len1 < cost ) {
               cost = len1;
               Q.push(Prefix(part, cost));
            }
         }
      }

   // using dijkstra
   while ( !Q.empty() ) {
      Substr str = Q.top().Node;
      int cost = Q.top().Cost;
      Q.pop();

      if ( C[str] != cost ) continue;
      if ( str.Len == 0 ) return cost;
      for ( int i = 0; i < N; i++ ) {
         const char *ptr1 = str.Ptr;
         const char *ptr2 = W[i];
         int len1 = str.Len, len2 = L[i];
         if ( len1 > len2 ) {
            swap(len1, len2);
            swap(ptr1, ptr2);
         }
         if ( equal(ptr1, ptr1+len1, ptr2) ) {
            Substr part(ptr2+len1, len2-len1);
            int &ncost = C[part];
            if ( ncost == 0 || cost + len1 < ncost ) {
               ncost = cost + len1;
               Q.push(Prefix(part, ncost));
            }
         }
      }
   }
   return -1;
}

void solve() {
   getchar();
   for ( int i = 0; i < N; i++ )
      L[i] = strlen(gets(W[i]));
   printf("%d\n", ambiguity());
}

int main() {
   while ( scanf("%d", &N), N ) solve();
   return 0;
}
