#include <stdio.h>
#include <math.h>
#pragma warning(disable:4996)

FILE* inp;
FILE* out;

void start(int i, int j, int* max, int* min) {
   int a = 1, b = 1;
   if (j != 1) {
      for (int k = 0; k < j - 2; k++) {
         b = a + b;
         a++;
      }
   }
   //공식 만듬

   if (j != 1) {
      *max = (i - b) / a;
      *min = ceil((i - a - b + 1) / (double)(a + 1));

   }
   else {
      *max = -1;
      *min = i;
   }

   if(1) {}
}

void line(int count) {
   int result = 0;
   int i, j;
   int min = 0, max = 0;
   int check = 0;

   for (int k = 0; k < count; k++) {
      result++;
      fscanf(inp, "%d %d", &i, &j);
      if (check == 0) {
         if (k == 0) {
            start(i, j, &max, &min);

         }
         else {
            int temp_min, temp_max;
            start(i, j, &temp_max, &temp_min);
            if ((temp_max < max && temp_max != -1) || max == -1) max = temp_max;
            if (temp_min > min) min = temp_min;

         }

         if (max == min && check == 0) {
            check = 1;
            fprintf(out, "%d %d\n", result, max);
         }
      }
   }
   if (check != 1) fprintf(out, "-1\n");
}

int main(void) {
   inp = fopen("line.inp", "rt");
   out = fopen("line.out", "wt");

   int num;
   int count;
   fscanf(inp, "%d", &num);

   for (int i = 0; i < num; i++) {
      fscanf(inp, "%d", &count);
      line(count);
   }
}