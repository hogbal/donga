#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <vector>
#include <stack>
#include <queue>
#pragma warning(disable:4996)
using namespace std;

FILE* inp;
FILE* out;

int root[500000];
int sub[500000];

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

int DFS(int start, vector<vector< int > > g) {
   bool visited[500000] = { false };

   vector<int> a;
   visited[start] = true;
   stack<int> s;
   s.push(start);
   int max = 1;

   while (!s.empty()) {
      int node = s.top();
      int size = g[node].size();
      s.pop();
      for (int i = 0; i < size; i++) {
         int next = g[node][i];
         if (visited[next] == false) {
            visited[next] = true;
            a.push_back(next);
            s.push(node);
            s.push(next);
            if (s.size() > max) max = s.size();
            break;
         }
      }
   }

   return max;
}


int family(int N) {
   int result;
   int r = -1;

   vector<vector< int > > p;
   p.resize(N + 1);

   for (int i = 0; i < N - 1; i++) {
      int a, b;
      fscanf(inp, "%d %d", &a, &b);
      root[i] = a;
      sub[i] = b;
      p[a].push_back(b);
   }
   sort(root, root + N - 1);
   sort(sub, sub + N - 1);

   for (int i = 0; i < N; i++) {
      sort(p[i].begin(), p[i].end());
   }

   int index_root = 0;
   int index_sub = 0;

   while (index_sub < N - 1 && index_root < N - 1) {
      if (root[index_root] > sub[index_sub]) {
         index_sub++;
      }
      else if (root[index_root] < sub[index_sub]) {
         int result = find(N - 1, root[index_root]);
         if (result == -1) {
            index_root++;
         }
         else {
            if (r != -1) {
               index_root++;
            }
            else {
               r = result;
               index_root++;
               break;
            }
         }
      }
      else {
         index_root++;
         index_sub++;
      }
   }
   //루트 찾아줌

   result = DFS(r, p);

   return result;
}

int main(void) {
   int TestCase;
   inp = fopen("family.inp", "rt");
   out = fopen("family.out", "wt");

   fscanf(inp, "%d", &TestCase);
   for (int i = 0; i < TestCase; i++) {
      int N;
      fscanf(inp, "%d", &N);
      fprintf(out,"%d\n",family(N));
   }
}