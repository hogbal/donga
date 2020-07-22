#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

FILE* inp;
FILE* out;

typedef struct {
   int num;
   int s;
   int b;
}Numgame;

void numgame(int count) {
   int check = 0;
   int *answer = (int*)malloc(sizeof(int)*9999);
   Numgame *ng = (Numgame*)malloc(sizeof(Numgame)*count);

   for (int i = 0; i < count; i++) {
      fscanf(inp, "%d %d %d", &ng[i].num, &ng[i].s, &ng[i].b);
   }

   for (int i = 1000; i <= 9999; i++) {

      int one = i / 1000;
      int two = i % 1000 / 100;
      int three = i % 1000 % 100 / 10;
      int four = i % 1000 % 100 % 10;
      int ch = 0;
      if (one == two || one == three || one == four || two == three || two == four || three == four || one == 0 || two == 0 || three == 0 || four == 0) {
         continue;
      }

      for (int j = 0; j < count; j++) {
         int check_s = ng[j].s, check_b = ng[j].b;
         int num, s = 0, b = 0;
         int temp_one = ng[j].num / 1000;
         int temp_two = ng[j].num % 1000 / 100;
         int temp_three = ng[j].num % 1000 % 100 / 10;
         int temp_four = ng[j].num % 1000 % 100 % 10;

         if (one == temp_two || one == temp_three || one == temp_four) b++;
         if (two == temp_one || two == temp_three || two == temp_four) b++;
         if (three == temp_one || three == temp_two || three == temp_four) b++;
         if (four == temp_one || four == temp_two || four == temp_three) b++;
         if (one == temp_one) s++;
         if (two == temp_two) s++;
         if (three == temp_three) s++;
         if (four == temp_four) s++;

         if (s == check_s && b == check_b) ch++;
         
      }

      if (ch == count) {
         answer[check] = i;
         check++;
      }
   }

   fprintf(out, "%d\n", check);
   if (check >= 6) {
      fprintf(out, "%d\n%d\n%d\n%d\n%d\n%d\n", answer[0], answer[1], answer[2], answer[check - 3], answer[check - 2], answer[check - 1]);
   }
   else {
      for (int i = 0; i < check; i++) fprintf(out, "%d\n", answer[i]);
   }
   

}

int main(void) {
   inp = fopen("numgame.inp", "rt");
   out = fopen("numgame.out", "wt");

   int count, num;
   fscanf(inp, "%d", &num);
   for (int i = 0; i < num; i++) {
      fscanf(inp, "%d", &count);
      numgame(count);

   }
}