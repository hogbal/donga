#include <stdio.h>
#pragma warning(disable:4996)

int gcd(int a, int b) {
   while (b != 0) {
      int r = a % b;
      a = b;
      b = r;
   }
   return a;
}

int fraction(int k) {
   int result = 0;
   int num = k + 1;
   while (1) {
      int denominator = num * k;
      int numerator = num - k;
      int gcd_num = gcd(denominator, numerator);
      denominator /= gcd_num;
      numerator /= gcd_num;
      if (numerator == 1) {
         result++;
         num++;
      }
      else {
         num++;
      }
   if (denominator < num) break;
   }

   return result;
}

int main(void) {
   FILE* inp = fopen("fraction.inp", "rt");
   FILE* out = fopen("fraction.out", "wt");

   int num;
   while (1) {
      fscanf(inp, "%d", &num);
      if (num == 0) break;
      fprintf(out, "%d\n", fraction(num));
   }
}