#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int n, m;

int paper(int N[], int M[]) {
   int result = 1;
   int line = 0;
   int N_plus = m - 1;
   int M_plus = m;
   int N_len = n * (m - 1);
   int M_len = m * (n - 1);
   int num = (n - 1)*(m - 1);

   for (int i = 0, j = 0, k = 0; k < num; i += N_plus, j += M_plus, k++) {
      int count = 0;
      if (N[i] == 0) count++;
      if (N[i + N_plus] == 0) count++;
      if (M[j] == 0) count++;
      if (M[j + 1] == 0) count++;

      if (count % 2 == 0) return 0;
      if (i + N_plus >= N_len || j + M_plus >= M_len) {
         line++;
         i = 0 + line - N_plus;
         j = 0 + line - M_plus;
      }
   }
   
   return result;
}

int main(void) {
   FILE* inp = fopen("paper.inp", "rt");
   FILE* out = fopen("paper.out", "wt");

   int testcase;
   
   fscanf(inp, "%d", &testcase);
   for (int i = 0; i < testcase; i++) {

      fscanf(inp, "%d %d", &n, &m);
      int *N = (int*)malloc(sizeof(int)*(n * (m - 1)));
      int *M = (int*)malloc(sizeof(int)*(m * (n - 1)));
      for (int j = 0; j < n * (m - 1); j++) {
         fscanf(inp, "%d", &N[j]);
      }
      printf("\n");
      for (int j = 0; j < m * (n - 1); j++) {
         fscanf(inp, "%d", &M[j]);
      }
      fprintf(out, "%d ", paper(N, M));
   }

}