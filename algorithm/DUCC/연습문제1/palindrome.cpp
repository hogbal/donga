#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream inp("palindrome.inp");
ofstream out("palindrome.out");

int palindrome(){
    string st,st_rev;
    inp >> st;
    st_rev = st;
    for(int i=0;i<st.size();i++) {
        st_rev[(st.size()-1)-i] = st[i];
    }
    
    for(int i=0;i<st.size();i++){
        if(st[i] >= '0' && st[i] <= '9') {  //숫자일 경우
            if(st[i] != st_rev[i]) {
                return 0;
            }
        }
        else {  //문자일 경우
            if(st[i] < st_rev[i]) {
                st[i] += 32;
                if(st[i] != st_rev[i]) {
                    return 0;
                }
            }
            else if(st[i] > st_rev[i]) {
                st_rev[i] += 32;
                if(st[i] != st_rev[i]) {
                    return 0;
                }
            }
        }
    }
    
    return 1;
}

int main(void) {
    int T;
    inp >> T;
    for(int i=0;i<T;i++) {
        out << palindrome() << endl;
    }
}
