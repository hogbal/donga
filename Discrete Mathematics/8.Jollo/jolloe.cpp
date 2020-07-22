#include <stdio.h>
#include <algorithm>
using namespace std;

int sy[3];
int dh[2];

int jolloe() {
   int sum[5];
   int result = 0;
   int index_first = -1;
   int index_second = -1;
   sort(sy, sy + 3);
   sort(dh, dh + 2);
   for (int i = 0; i < 3; i++) {
      if (dh[0] < sy[i]) {
         index_first = i;
         break;
      }
   }

   if (index_first == 1 || index_first == 2) {
      for (int i = index_first + 1; i < 3; i++) {
         if (dh[1] < sy[i]) {
            return -1;
         }
      }
      if (index_first == 1) {
         result = sy[2] + 1;
      }
      else if (index_first == 2) {
         result = sy[1] + 1;
      }
   }
   else if (index_first == 0) {
      if (sy[2] < dh[1]) {
         result = sy[2] + 1;
      }
   }
   else {   //왕자 카드 2개다 공주 이길경우
      result = 1;
   }

   for (int i = 0; i < 3; i++) {
      sum[i] = sy[i];
   }
   for (int i = 0; i < 2; i++) {
      sum[i + 3] = dh[i];
   }
   sort(sum, sum + 5);
   for (int i = 0; i < 5; i++) {
      if (sum[i] == result) {
         result++;
         i--;
      }
   }
   if (result == 0) result = -1;
   if (result > 52) result = -1;
   return result;
}

int main(void) {
   FILE* inp = fopen("jolloe.inp", "rt");
   FILE* out = fopen("jolloe.out", "wt");

   while (1) {
      fscanf(inp, "%d %d %d %d %d", &sy[0], &sy[1], &sy[2], &dh[0], &dh[1]);
      if (sy[0] == 0) break;
      fprintf(out, "%d\n", jolloe());
   }
}