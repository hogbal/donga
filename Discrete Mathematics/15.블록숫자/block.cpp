#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

FILE* inp;
FILE* out;

int Len(int line) {
   int sum = 0;
   sum = (line * (line + 1)) / 2;
   return sum;
}

void print(int* arr, int line) {
   int check = 1;
   int plus = 1;
   for (int i = 1; i < Len(line) + 1; i++) {

      fprintf(out, "%d", arr[i]);
      if (plus == check) {
         fprintf(out, "\n");
         check = 1;
         plus++;
      }
      else {
         fprintf(out, " ");
         check++;
      }
   }
}

void block(int* arr, int line) {
   int l = 1;
   int check = 1;
   int exit = 1;
   while (1) {
      if (exit == 0) break;
      if (line == 1) break;
      exit = 0;
      l = 1;
      check = 1;
      for (int i = 1; i <= Len(line) - line; i++) {
         int count = 0;
         int p_node = 0;
         int c1_node = 0;
         int c2_node = 0;
         int index = i + l;

         if (arr[i] != -1) {
            count++;
            p_node = 1;
         }
         if (arr[index] != -1) {
            count++;
            c1_node = 1;
         }
         if (arr[index + 1] != -1) {
            count++;
            c2_node = 1;
         }

         if (count == 2) {
            exit = 1;
            if (p_node == 0) {
               arr[i] = (arr[index] + arr[index + 1]) % 100;
            }
            else if (c1_node == 0) {
               if (arr[i] > arr[index + 1]) {
                  arr[index] = arr[i] - arr[index + 1];
                  arr[index] %= 100;
               }
               else {
                  arr[index] = 100 + arr[i] - arr[index + 1];
                  arr[index] %= 100;
               }
            }
            else {
               if (arr[i] > arr[index]) {
                  arr[index + 1] = arr[i] - arr[index];
                  arr[index + 1] %= 100;
               }
               else {
                  arr[index + 1] = 100 + arr[i] - arr[index];
                  arr[index + 1] %= 100;
               }
            }
         }
         if (l == check) {
            l++;
            check = 1;
         }
         else {
            check++;
         }
      }
   }
}

int main(void) {
   inp = fopen("block.inp", "rt");
   out = fopen("block.out", "wt");

   int testcase;
   fscanf(inp, "%d", &testcase);
   for (int i = 0; i < testcase; i++) {
      int line;
      fscanf(inp, "%d", &line);

      int* arr = (int*)malloc(sizeof(int) * (Len(line) + 1));

      for (int j = 0; j < Len(line); j++) {
         fscanf(inp, "%d", &arr[j + 1]);
      }

      block(arr, line);
      print(arr, line);
   }
}