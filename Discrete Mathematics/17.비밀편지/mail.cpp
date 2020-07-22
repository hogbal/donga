#include <iostream>
#include <string>
#include <fstream>
#pragma warning(disable:4996)
using namespace std;

ifstream inp("mail.inp");
ofstream out("mail.out");

string A_str = "000000";
string B_str = "001111";
string C_str = "010011";
string D_str = "011100";
string E_str = "100110";
string F_str = "101001";
string G_str = "110101";
string H_str = "111010";

int print(string pw) {

   if (pw == A_str) out << "A";
   else if (pw == B_str) out << "B";
   else if (pw == C_str) out << "C";
   else if (pw == D_str) out << "D";
   else if (pw == E_str) out << "E";
   else if (pw == F_str) out << "F";
   else if (pw == G_str) out << "G";
   else if (pw == H_str) out << "H";
   else return 0;
   return 1;
}

int compare(string pw) {

   int check = 0;
   for (int i = 0; i < 6; i++) {
      if (pw.at(i) == '0') pw.at(i) = '1';
      else pw.at(i) = '0';
      if (print(pw)) {
         check = 1;
         break;
      }

      if (pw.at(i) == '0') pw.at(i) = '1';
      else pw.at(i) = '0';
   }
   return check;
}

int main(void) {
   string pw;
   int count;
   int num;
   inp >> count;
   for (int i = 0; i < count; i++) {
      if (inp.eof()) break;
      inp >> num;
      inp >> pw;
      int j = 0;
      for (int i = 0; i < num; i++) {
         string temp = pw.substr(j, 6);
         j += 6;
         if (!print(temp)) {
            if (!compare(temp)) {
               out << "X";
            }
         }
      }
      out << endl;
   }

}