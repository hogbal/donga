#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int array[21] = { 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

int check(int a, int b) {
   int result = 0;
   int nm;
   for (int i = a; i <= b; i++) {
      int num[6];
      for (int j = 0; j < 6; j++) {
         num[j] = 0;
      }
      int index = 0;
      int n = i;
      int one = 0;

      while (n) {
         if (n % 10 == 0) {
            n /= 10;
         }

         else {
            num[index++] = n % 10;
            if (n % 10 == 1) {
               one++;
            }
            n /= 10;
         }
      }
      if (one >= 2) {
         result++;
         continue;
      }
      int nm;
      int first_index = 0;
      int second_index = 0;
      int ch = 0;

      for (int j = 0; j < index; j++) {
         nm = 0;
         if (ch == 1) break;
         for (int k = first_index; k < index; k++) {
            if (num[k] == 1 || num[k] == 3 || num[k] == 7 || num[k] == 9) {
               nm = num[k];
               first_index = k + 1;
               break;
            }
         }
         if (nm == 0) break;
         second_index = 0;
         for (int t = 0; t < index; t++) {
            if (ch == 1) break;
            nm = num[first_index - 1];
            for (int k = second_index; k < index; k++) {
               if (num[k] != nm) {
                  nm = nm + (num[k] * 10);
                  second_index = k + 1;
                  break;
               }
            }

            for (int k = 0; k < 21; k++) {
               if (array[k] == nm) {
                  result++;
                  ch = 1;
                  break;
               }
            }
         }
      }
   }
   return result;
}

int main(void) {
   FILE* inp = fopen("2digit_prime.inp", "rt");
   FILE* out = fopen("2digit_prime.out", "wt");
   int num;
   int a, b;

   fscanf(inp, "%d", &num);


   for (int i = 0; i < num; i++) {
      fscanf(inp, "%d %d", &a, &b);
      fprintf(out, "%d\n", check(a, b));
   }
   fclose(inp);
   fclose(out);
}