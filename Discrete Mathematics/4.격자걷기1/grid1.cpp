#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int grid_type1(int N, int M, int t, int s, int k) {
   int count = N * M;
   int result;
   int index = 1;
   int p = 1, m = 0;
   int len = 0;
   int count1 = 0;

   if (s == 1 || s == 3) {
      while (1) {
         result = index;
         len++;
         if (len == k) break;
         if (p == 1) {
            if (count1 == M-1) {
               p = 0;
               m = 1;
               index += M;
               count1 = 0;
            }
            else {
               index++;
               count1++;
            }
         }
         else if (m == 1) {
            if (count1 == M-1) {
               p = 1;
               m = 0;
               index += M;
               count1 = 0;
            }
            else {
               index--;
               count1++;
            }
         }
      }
   }
   if (s == 2 || s == 4) {
      index = M;
      m = 1;
      p = 0;
      while (1) {
         result = index;
         len++;
         if (len == k) break;
         if (p == 1) {
            if (count1 == M-1) {
               p = 0;
               m = 1;
               index += M;
               count1 = 0;
            }
            else {
               index++;
               count1++;
            }
         }
         else if (m == 1) {
            if (count1 == M-1) {
               p = 1;
               m = 0;
               index += M;
               count1 = 0;
            }
            else {
               index--;
               count1++;
            }
         }
      }
   }
   if (s == 3 || s == 4) {
      result = M * N + 1 - result;
   }
   return result;
}

int grid_type2(int N, int M, int t, int s, int k) {
   int count = N * M;
   int result;
   int index = 1;
   int p = 1, m = 0;
   int len = 0;
   int count1 = 0;

   if (s == 1 || s == 3) {
      while (1) {
         result = index;
         len++;
         if (len == k) break;
         if (p == 1) {

            if (count1 == N-1) {
               p = 0;
               m = 1;
               index++;
               count1 = 0;
            }
            else {
               count1++;
               index += M;
            }
         }
         else if (m == 1) {
            if (count1 == N-1) {
               p = 1;
               m = 0;
               index++;
               count1 = 0;
            }
            else {
               index -= M;
               count1++;
            }
         }
      }
   }
   if (s == 2 || s == 4) {
      index = M;
      while (1) {
         result = index;
         len++;
         if (len == k) break;
         if (p == 1) {
            if (count1 == N - 1) {
               count1 = 0;
               p = 0;
               m = 1;
               index--;
            }
            else {
               index += M;
               count1++;
            }
         }
         else if (m == 1) {
            if (count1 == N-1) {
               p = 1;
               m = 0;
               index--;
               count1 = 0;
            }
            else {
               index -= M;
               count1++;
            }
         }
      }
   }

   if (s == 3 || s == 4) {
      result = M * N + 1 - result;
   }
   return result;
}

int main(void) {
   FILE* inp = fopen("grid1.inp", "rt");
   FILE* out = fopen("grid1.out", "wt");

   int num;
   int N, M, t, s, k;
   fscanf(inp, "%d", &num);
   for (int i = 0; i < num; i++) {
      fscanf(inp, "%d %d %d %d %d", &N, &M, &t, &s, &k);
      if (t == 1) {
         fprintf(out, "%d\n", grid_type1(N, M, t, s, k));
      }
      else if (t == 2) {
         fprintf(out, "%d\n", grid_type2(N, M, t, s, k));
      }
   }

}