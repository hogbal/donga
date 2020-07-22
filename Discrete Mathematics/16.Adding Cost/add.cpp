#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <queue>
#pragma warning(disable:4996)
using namespace std;

ifstream inp("add.inp");
ofstream out("add.out");

int main(void) {
   int num;
   while (1) {
      priority_queue< long long, vector<long long>, greater<long long> > hp;
      inp >> num;
      if (num == 0) break;
      for (int i = 0; i < num; i++) {
         long long temp;
         inp >> temp;
         hp.push(temp);
      }
      long long cost = 0;
      while (hp.size() != 1) {
         long long temp1 = hp.top();
         hp.pop();
         long long temp2 = hp.top();
         hp.pop();
         hp.push(temp1 + temp2);
         cost += (temp1 + temp2);
      }
      out << cost << endl;
   }
}