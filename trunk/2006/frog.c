#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#define MAX_RANGE 8

typedef struct {
   int r;
   int c;
} Point;
Point max;

struct PointList{
   Point point;
   int weigth;
   struct PointList* next;
};

int current;

int edges[5][5] = {
   {7, 6, 5, 6, 7},
   {6, 3, 2, 3, 6},
   {5, 2, 0, 2, 5},
   {6, 3, 2, 3, 6},
   {7, 6, 5, 6, 7}
};

struct PointList *makePointListNode(Point p, int w, struct PointList* next){
   struct PointList *pl = (struct PointList*)
      malloc(sizeof(struct PointList));
   pl->point = p;
   pl->weigth = w;
   pl->next = next;
   return pl;
}

void fillMatrix(int m[][max.c], int x1, int y1, int x2, int y2, int val){
   assert(0 <= x1); assert(x1 <= x2);
   assert(0 <= x2); assert(x2 < max.c);
   
   assert(0 <= y1); assert(y1 <= y2);
   assert(0 <= y2); assert(y2 < max.r);
   int i,j;
   for(j = y1; j <= y2; j++)
      for(i = x1; i <= x2; i++)
         m[j][i] = val;
}

int getLess(struct PointList* lst[], Point* p, int *w){
   int first = current;
   while(!lst[current]){
      current = (current + 1) % MAX_RANGE;
      if(first == current) return 0;
   }
   *p = lst[current]->point;
   *w = lst[current]->weigth;
   struct PointList* tmp = lst[current];
   free(tmp);
   lst[current] = lst[current]->next;
   return 1;
}
void addPoint(struct PointList* lst[], Point p, int w){
   int idx = w % MAX_RANGE;
   lst[idx] = makePointListNode(p,w,lst[idx]);
}

void dijsktra(int marsh[][max.c], int cost[][max.c], Point s){
   cost[s.r][s.c] = 0;

   struct PointList* list[MAX_RANGE];
   int x;
   for(x = 0; x < MAX_RANGE; x++)
      list[x]=0;

   addPoint(list, s, cost[s.r][s.c]);

   Point p;
   int w;
   while(getLess(list, &p, &w)){
      if(w <= cost[p.r][p.c]){
         cost[p.r][p.c] = w;
         int i, j;
         for(j = 0; j < 5; j++)
            for(i = 0; i < 5; i++){
               Point adj;
               adj.r = p.r + (j - 2);
               adj.c = p.c + (i - 2);
               if( !(i == 2 && j == 2) &&
                   0 <= adj.r && adj.r < max.r &&
                   0 <= adj.c && adj.c < max.c &&
                   marsh[adj.r][adj.c] &&
                   w + edges[j][i] < cost[adj.r][adj.c]){
                  cost[adj.r][adj.c] = w + edges[j][i];
                  addPoint(list, adj, cost[adj.r][adj.c]);
               }
            }
      }
   }
}

int main(int argc, char *argv[]){
   scanf("%d %d", &max.c, &max.r);
   
   while(!(max.c == 0 && max.r == 0)){
      int marsh[max.r][max.c];
      fillMatrix(marsh, 0, 0, max.c-1, max.r-1, 1);
      
      int cost[max.r][max.c];
      fillMatrix(cost, 0, 0, max.c-1, max.r-1, INT_MAX);
      
      Point frog, toad;
      scanf("%d %d %d %d", &frog.c, &frog.r, &toad.c, &toad.r);
      frog.c--; frog.r--; toad.c--; toad.r--;
      
      int w;
      scanf("%d", &w);
      
      while(w > 0){
         int c1, r1, c2, r2;
         scanf("%d %d %d %d", &c1, &r1 , &c2, &r2);
         fillMatrix(marsh, c1-1, r1-1, c2-1, r2-1, 0);
         w--;
      }

      dijsktra(marsh, cost, frog);

      if(cost[toad.r][toad.c] == INT_MAX)
         printf("impossible\n");
      else
         printf("%d\n",cost[toad.r][toad.c]);

      scanf("%d %d", &max.c, &max.r);
   }
   return 0;
}

