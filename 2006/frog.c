#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
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

int getLess(struct PointList* lst[], Point* p, int *w){
   struct PointList* tmp;
   int first = current;
   while(!lst[current]){
      current = (current + 1) % MAX_RANGE;
      if(first == current) return 0;
   }
   *p = lst[current]->point;
   *w = lst[current]->weigth;
   tmp = lst[current];
   lst[current] = lst[current]->next;
   free(tmp);
   return 1;
}
void addPoint(struct PointList* lst[], Point p, int w){
   int idx = w % MAX_RANGE;
   struct PointList* next = lst[idx];
   lst[idx] = (struct PointList*)malloc(sizeof(struct PointList));
   lst[idx]->point = p;
   lst[idx]->weigth = w;
   lst[idx]->next = next;
}

void dijsktra(int marsh[][max.c], int cost[][max.c], Point s, Point t){
   struct PointList* list[MAX_RANGE];
   int x;
   Point p;
   int w;

   cost[s.r][s.c] = 0;
   for(x = 0; x < MAX_RANGE; x++)
      list[x]=0;

   addPoint(list, s, cost[s.r][s.c]);

   while(getLess(list, &p, &w)){
      if(w <= cost[p.r][p.c]){
         int i, j;
         cost[p.r][p.c] = w;
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
      int cost[max.r][max.c];
      Point frog, toad;
      int w;
      int i,j;

      for(j = 0; j < max.r; j++)
         for(i = 0; i < max.c; i++){
            marsh[j][i] = 1;
            cost[j][i] = INT_MAX;
         }
      
      scanf("%d %d %d %d", &frog.c, &frog.r, &toad.c, &toad.r);
      frog.c--; frog.r--; toad.c--; toad.r--;
      
      scanf("%d", &w);
      
      while(w > 0){
         int c1, r1, c2, r2;
         scanf("%d %d %d %d", &c1, &r1, &c2, &r2);
         for(j = r1 - 1; j < r2; j++)
            for(i = c1 - 1; i < c2; i++)
               marsh[j][i] = 0;
         w--;
      }

      dijsktra(marsh, cost, frog, toad);

      if(cost[toad.r][toad.c] == INT_MAX)
         printf("impossible\n");
      else
         printf("%d\n",cost[toad.r][toad.c]);

      scanf("%d %d", &max.c, &max.r);
   }
   return 0;
}

