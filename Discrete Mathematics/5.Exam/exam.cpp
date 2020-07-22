#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

FILE* inp;
FILE* out;

char* input(int* len) {
   char temp[1000];
   fscanf(inp, "%s", temp);

   for (int i = 0; temp[i] != 0; i++) (*len)++;
   char* in = (char*)malloc(sizeof(char) * (*len));
   for (int i = 0; i < *len; i++) {
      in[i] = temp[i];
   }
   return in;
}

int exam(char* good_st, char* P, char* Q, int offset, int len_Q, int len) {
   int result;
   int index = 0;
   int temp;
   int star = 0;

   for (int i = 0; i < len_Q; i++) {
      if (P[index] == '?') {
         int check = 1;
         for (int j = 0; j < len; j++) {
            if (Q[i] == good_st[j]) {
               check = 0;
               break;
            }
         }
         if (check == 1) return 0;
         index++;
      }
      else if (P[index] == '*') {
         i = i + offset;
         temp = index;
         star = 1;
         index++;
      }
      else {
         if (P[index] != Q[i]) {
            return 0;
         }
         else index++;
      }
   }
   int check = offset + 1;
   if (offset < 0) check = 1;
   else {
      if (star == 1) {
         for (int i = temp; i <= offset + temp; i++) {
            for (int j = 0; j < len; j++) {
               if (Q[i] == good_st[j]) {
                  check--;
                  break;
               }
            }
         }
      }
   }
   if (check == 0) return 0;
   else return 1;
}

int main(void) {
   inp = fopen("exam.inp", "rt");
   out = fopen("exam.out", "wt");

   int num;
   char* good_st;
   char* P;
   char* Q;
   int count;


   fscanf(inp, "%d", &num);
   for (int i = 0; i < num; i++) {
      int len_P = 0;
      int len_Q = 0;
      int len_good_st = 0;
      good_st = input(&len_good_st);
      P = input(&len_P);
      fscanf(inp, "%d", &count);

      fprintf(out, "Test Case: #%d\n", i + 1);
      for (int j = 0; j < count; j++) {
         Q = input(&len_Q);
         int offset = len_Q - len_P;
         if (exam(good_st, P, Q, offset, len_Q, len_good_st) == 1) {
            fprintf(out, "Yes\n");
         }
         else {
            fprintf(out, "No\n");
         }
         len_Q = 0;
      }
   }

}