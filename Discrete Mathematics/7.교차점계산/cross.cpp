#include <stdio.h>
#include <stdlib.h>

int n1[10000];
int n2[10000];
int n3[10000];

int cross(int count) {
   int result = 0;
   for (int i = 0; i < count; i++) {
      for (int j = 0; j < count; j++) {

         if (n1[i] == n2[j]) {
            n3[i] = j;
            break;
         }
      }
   }//입력끝

   for (int i = 0; i < count; i++) {
      for (int j = i; j < count; j++) {
         if (n3[i] > n3[j]) result++;
      }
   }
   return result;
}

int main(void) {
   FILE* inp = fopen("cross.inp", "rt");
   FILE* out = fopen("cross.out", "wt");

   int num;
   int count;
   int num1;

   fscanf(inp, "%d", &num);
   for (int i = 0; i < num; i++) {
      fscanf(inp, "%d", &count);
      for (int i = 0; i < count; i++) {
         fscanf(inp, "%d", &num1);
         n1[i] = num1;
      }
      for (int i = 0; i < count; i++) {
         fscanf(inp, "%d", &num1);
         n2[i] = num1;
      }
      fprintf(out, "Case %d: %d\n", i + 1, cross(count));
   }

}