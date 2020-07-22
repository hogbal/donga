#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>
#pragma warning(disable:4996)
using namespace std;

ifstream in("spreadsheet.inp");
ofstream out("spreadsheet.out");

char tr(int num) {
   if (num == 1) return 'A';
   else if (num == 2) return 'B';
   else if (num == 3) return 'C';
   else if (num == 4) return 'D';
   else if (num == 5) return 'E';
   else if (num == 6) return 'F';
   else if (num == 7) return 'G';
   else if (num == 8) return 'H';
   else if (num == 9) return 'I';
   else if (num == 10) return 'J';
   else if (num == 11) return 'K';
   else if (num == 12) return 'L';
   else if (num == 13) return 'M';
   else if (num == 14) return 'N';
   else if (num == 15) return 'O';
   else if (num == 16) return 'P';
   else if (num == 17) return 'Q';
   else if (num == 18) return 'R';
   else if (num == 19) return 'S';
   else if (num == 20) return 'T';
   else if (num == 21) return 'U';
   else if (num == 22) return 'V';
   else if (num == 23) return 'W';
   else if (num == 24) return 'X';
   else if (num == 25) return 'Y';
   else if (num == 26 || num == 0) return 'Z';

}

void get_num(int a, int r) {
   if (a < r) {
      if (a != 0) out << tr(a);
   }
   else {
      if (a % r == 0) {
         get_num(a / r - 1, r);
      }
      else get_num(a / r, r);
      out << tr(a % r);
   }
}

void spreadsheet(string st) {
   if (st.at(1) >= '0' && st.at(1) <= '9' && st.at(0) == 'R') {
      int C_index = st.find('C');
      string C = st.substr(C_index + 1, st.size());
      string R = st.substr(1, C_index - 1);
      int C_num = 0;

      for (int i = 0; i < C.size(); i++) {
         C_num += (C.at(i) - '0') * pow(10, C.size() - i - 1);
      }

      get_num(C_num, 26);
      out << R << endl;
   }
   else {

      int index = 0;
      for (int i = 0; i < st.size(); i++) {
         if (st.at(i) >= '0' && st.at(i) <= '9') {
            index = i;
            break;
         }
      }

      string R = st.substr(index, st.size());
      string C = st.substr(0, index);
      out << "R" << R << "C";
      
      int sum = 0;

      for (int i = 0; i < C.size(); i++) {
         sum += ((C.at(i) - 'A') + 1) * pow(26, C.size() - 1 - i);
      }
      out << sum << endl;
   }
}

int main(void) {
   string n;

   int num;
   in >> num;
   for (int i = 0; i < num; i++) {
      in >> n;
      spreadsheet(n);
   }

}