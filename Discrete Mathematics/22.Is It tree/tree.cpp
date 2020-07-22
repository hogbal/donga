#include <stdio.h>
#include <vector>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

FILE* inp;
FILE* out;

int root[1000000];
int sub[1000000];

int find(int len, int f) {
   int left = 0;
   int right = len;
   while (left <= right) {
      int center = (left + right) / 2;
      if (sub[center] > f) {
         right = center - 1;
      }
      else if (sub[center] < f) {
         left = center + 1;
      }
      else {
         return -1;
      }
   }
   return f;
}

int tree(int len) {
   int r = -1;
   sort(root, root + len);
   sort(sub, sub + len);
   int index_root = 0;
   int index_sub = 0;

   while (index_sub < len - 1) {
      if (sub[index_sub] == sub[index_sub + 1]) return -1;
      index_sub++;
   }
   index_sub = 0;

   while (index_sub < len && index_root < len) {
      if (root[index_root] > sub[index_sub]) {
         index_sub++;
      }
      else if (root[index_root] < sub[index_sub]) {
         int result = find(len, root[index_root]);
         if (result == -1) {
            index_root++;
         }
         else {
            if (r != -1) {
               if (r != result) {
                  return -1;
               }
               else {
                  index_root++;
               }
            }
            else {
               r = result;
               index_root++;
            }
         }
      }
      else {
         index_root++;
         index_sub++;
      }
   }

   return r;
}

int main(void) {
   inp = fopen("tree.inp", "rt");
   out = fopen("tree.out", "wt");
   int num1, num2;
   int TC = 1;

   while (1) {
      int index = 0;
      do {
         fscanf(inp, "%d %d", &num1, &num2);
         if (num1 == -1 && num2 == -1) break;
         else if (num1 == 0 && num2 == 0) continue;
         else {
            root[index] = num1;
            sub[index] = num2;
            index++;
         }
      } while (!((num1 == 0 && num2 == 0) || (num1 == -1 && num2 == -1)));
      if (num1 == -1 && num2 == -1) break;
      else if (num1 == 0 && num2 == 0) {
         fprintf(out, "Test Case %d: %d\n", TC++, tree(index));
         continue;
      }
   }
}