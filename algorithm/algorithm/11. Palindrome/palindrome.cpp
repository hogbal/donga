#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

ifstream inp("palindrome.inp");
ofstream out("palindrome.out");

string st1,st2;

void palindrome() {
    int len = st1.size();
    int **mat = new int*[len+1];
    for(int i=0;i<len+1;i++) {
        mat[i] = new int[len+1];
    }
    
    for(int i=0;i<len+1;i++) {
        mat[0][i] = 0;
        mat[i][0] = 0;
    }
    
    for(int i=1;i<len+1;i++) {
        for(int j=1;j<len+1;j++) {
            if(st2[i-1] == st1[j-1]) {
                mat[i][j] = mat[i-1][j-1] + 1;
            }
            else {
                if(mat[i][j-1] > mat[i-1][j]) {
                    mat[i][j] = mat[i][j-1];
                }
                else {
                    mat[i][j] = mat[i-1][j];
                }
            }
        }
    }
    
    int result = len-mat[len][len];
    if(result < 3) {
        out << result << endl;
    }
    else {
        out << "-1" << endl;
    }
    
    for (int i = 0; i < len+1; i++)
            delete [] mat[i];
        delete [] mat;
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        inp >> st1;
        st2 = st1;
        reverse(st2.begin(), st2.end());
        
        palindrome();
    }
}
