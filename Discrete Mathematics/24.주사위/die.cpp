#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

FILE* inp;
FILE* out;

typedef struct {
   int N;
   int W;
   int S;
   int E;
}Direction;

int find(int* Dice, int f) {
   for (int i = 0; i < 6; i++) {
      if (f == Dice[i]) return i;
   }
   return -1;
}

void tumble_N(int* Dice) {
   int temp[6];
   for (int i = 0; i < 6; i++) {
      temp[i] = Dice[i];
   }
   Dice[0] = temp[4];
   Dice[1] = temp[0];
   Dice[2] = temp[1];
   Dice[4] = temp[2];

}

void tumble_W(int* Dice) {
   int temp[6];
   for (int i = 0; i < 6; i++) {
      temp[i] = Dice[i];
   }
   Dice[0] = temp[3];
   Dice[2] = temp[5];
   Dice[3] = temp[2];
   Dice[5] = temp[0];

}


void tumble_S(int* Dice) {
   int temp[6];
   for (int i = 0; i < 6; i++) {
      temp[i] = Dice[i];
   }

   Dice[0] = temp[1];
   Dice[1] = temp[2];
   Dice[2] = temp[4];
   Dice[4] = temp[0];

}

void tumble_E(int* Dice) {
   int temp[6];
   for (int i = 0; i < 6; i++) {
      temp[i] = Dice[i];
   }

   Dice[0] = temp[5];
   Dice[2] = temp[3];
   Dice[3] = temp[0];
   Dice[5] = temp[2];

}

void start(int* Dice, int Top, int Front) {
   while (1) {
      int Front_index = find(Dice, Front);
      if (Front_index == 1) break;
      if (Front_index == 3 || Front_index == 5) {
         tumble_E(Dice);
      }
      else {
         tumble_S(Dice);
      }
   }

   while (1) {
      int Top_index = find(Dice, Top);
      if (Top_index == 2) break;
      tumble_E(Dice);
   }
}

void die(int *Dice,int Top, int Front) {

   start(Dice, Top, Front);

   int N;
   fscanf(inp, "%d", &N);
   Direction dir = {};
   char ch;
   fscanf(inp, "%c", &ch);
   for (int i = 0; i < N; i++) {
      fscanf(inp, "%c", &ch);
      switch (ch)
      {
      case 'N':
         tumble_N(Dice);
         dir.N++;
         break;
      case 'W':
         tumble_W(Dice);
         dir.W++;
         break;
      case 'S':
         tumble_S(Dice);
         dir.S++;
         break;
      case 'E':
         tumble_E(Dice);
         dir.E++;
         break;
      }
   }
   fprintf(out, "%d %d", dir.E - dir.W, dir.N - dir.S);
   fprintf(out, " %d %d\n", Dice[2], Dice[1]);
}

int main(void) {
   inp = fopen("die.inp", "rt");
   out = fopen("die.out", "wt");

   int T;
   fscanf(inp, "%d", &T);
   for (int i = 0; i < T; i++) {
      int Dice[6];

      for (int j = 0; j < 6; j++) {
         fscanf(inp, "%d", &Dice[j]);
      }

      int Top, Front;
      fscanf(inp, "%d %d", &Top, &Front);
      die(Dice, Top, Front);
   }

}