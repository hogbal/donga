#include stdio.h
#include stdlib.h
#pragma warning(disable4996)

int check(int a, int b) {
   int count = 0;
   int result = 0;
   for (int i = a; i = b; i++) {
      for (int j = 1; j  j = i; j++) {
         if (i % j == 0) { 
            count++; 
            if (j  j  i) { 
               count++;
            } 
         }

      }
      if (i % count == 0) {
         result++;
      }
      count = 0;
   }
   return result;
}

int main(void) {

   FILE inp;
   FILE out;
   int num;
   int a, b;

   inp = fopen(divisor.inp, rt);
   
   if (inp == NULL) {
      fprintf(stderr, inp error);
   }

   out = fopen(divisor.out, wt);

   if (out == NULL) {
      fprintf(stderr, out error);
   }

   fscanf(inp, %d, &num);
   if (num  50) {
      fprintf(stderr, num  50);
      return 0;
   }
   for (int i = 0; i  num; i++) {
      fscanf(inp, %d %d, &a, &b);
      if (a  b  b  1000000  b - a  1000) {
         fprintf(stderr, error);
      }
      else {
         fprintf(out, %dn, check(a, b));
      }
   }
}