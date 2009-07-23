#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]){
   int N,C,K;
   scanf("%d %d %d", &N, &C, &K);
   while(!(N ==  0 && C == 0 && K == 0)){
      int min = INT_MAX;
      int cont[K];
      int i;
      for(i = 0; i < K; i++) cont[i] = 0;
      while(N > 0){
         int c = C;
         while(c > 0){
            int x;
            scanf("%d", &x);
            cont[x-1]++;
            c--;
         }
         N--;
      }
      for(i = 0; i < K; i++)
         if(cont[i] < min) min = cont[i];

      i=0;
      while(i < K){
         if(cont[i] == min){
            printf("%d", i+1);
            i++;
            break;
         }
         i++;
      }
      while(i < K){
         if(cont[i] == min)
            printf(" %d", i+1);
         i++;
      }
      printf("\n");
      scanf("%d %d %d", &N, &C, &K);
   }            
   return 0;
}
