#include <stdio.h>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

FILE* inp;
FILE* out;

struct Card {
   int picture;
   int num;
};

char output_pic(int pic) {
   if (pic == 1) return 'C';
   else if (pic == 2) return 'D';
   else if (pic == 3) return 'S';
   else if (pic == 4) return 'H';
}

char output_num(int num) {
   if (num == 10) return 'T';
   else if (num == 11) return 'J';
   else if (num == 12) return 'Q';
   else if (num == 13) return 'K';
   else if (num == 14) return 'A';
   else return num + '0';
}

void card_print(Card *S, Card *W, Card*N, Card* E) {
   fprintf(out, "S: ");
   for (int i = 0; i < 13; i++) {
      fprintf(out, "%c%c ", output_pic(S[i].picture), output_num(S[i].num));
   }
   fprintf(out, "\nW: ");
   for (int i = 0; i < 13; i++) {
      fprintf(out, "%c%c ", output_pic(W[i].picture), output_num(W[i].num));
   }
   fprintf(out, "\nN: ");
   for (int i = 0; i < 13; i++) {
      fprintf(out, "%c%c ", output_pic(N[i].picture), output_num(N[i].num));
   }
   fprintf(out, "\nE: ");
   for (int i = 0; i < 13; i++) {
      fprintf(out, "%c%c ", output_pic(E[i].picture), output_num(E[i].num));
   }
   fprintf(out, "\n");
}

bool cmp_pic(const Card &p1, const Card &p2) {
   return p1.picture < p2.picture;
}

bool cmp_num(const Card &p1, const Card &p2) {
   if ((p1.num < p2.num) && (p1.picture == p2.picture)) {
      return true;
   }
   else {
      return false;
   }
}

int input_pic(char pic) {
   if (pic == 'C') return 1;
   else if (pic == 'D') return 2;
   else if (pic == 'S') return 3;
   else if (pic == 'H') return 4;
}

int input_num(char num) {
   if (num == 'T') {
      num = 10;
   }
   else if (num == 'J') {
      num = 11;
   }
   else if (num == 'Q') {
      num = 12;
   }
   else if (num == 'K') {
      num = 13;
   }
   else if (num == 'A') {
      num = 14;
   }
   else {
      num = num - '0';
   }
   return num;
}

void bridge(char dealer) {
   Card S[13];
   Card W[13];
   Card N[13];
   Card E[13];
   int s = 0, w = 0, n = 0, e = 0;
   int index_S = 0, index_W = 0, index_N = 0, index_E = 0;
   if (dealer == 'S') w = 1;
   else if (dealer == 'W') n = 1;
   else if (dealer == 'N') e = 1;
   else if (dealer == 'E') s = 1;

   char enter;
   fscanf(inp, "%c", &enter);

   for (int i = 0;; i++) {
      char num;
      char picture;
      if (i == 26) {
         fscanf(inp, "%c", &enter);
         continue;
      }
      if (i == 53) break;
      fscanf(inp, "%c%c", &picture, &num);
      if (s == 1) {
         s = 0;
         w = 1;
         S[index_S].picture = input_pic(picture);
         S[index_S].num = input_num(num);
         index_S++;
      }
      else if (w == 1) {
         w = 0;
         n = 1;
         W[index_W].picture = input_pic(picture);
         W[index_W].num = input_num(num);
         index_W++;
      }
      else if (n == 1) {
         n = 0;
         e = 1;
         N[index_N].picture = input_pic(picture);
         N[index_N].num = input_num(num);
         index_N++;
      }
      else if (e == 1) {
         e = 0;
         s = 1;
         E[index_E].picture = input_pic(picture);
         E[index_E].num = input_num(num);
         index_E++;
      }
   }
      
   sort(S, S + 13, cmp_pic);
   sort(S, S + 13, cmp_num);
   sort(W, W + 13, cmp_pic);
   sort(W, W + 13, cmp_num);
   sort(N, N + 13, cmp_pic);
   sort(N, N + 13, cmp_num);
   sort(E, E + 13, cmp_pic);
   sort(E, E + 13, cmp_num);

   card_print(S, W, N, E);
}

int main(void) {
   inp = fopen("bridge.inp", "rt");
   out = fopen("bridge.out", "wt");

   char dealer;
   fscanf(inp, "%c", &dealer);
   while (1) {
      if (dealer == '#') break;
      bridge(dealer);
      fscanf(inp, "%c", &dealer);
      if(dealer == '\n') fscanf(inp, "%c", &dealer);
   }

}