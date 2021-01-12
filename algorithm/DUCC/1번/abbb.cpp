#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream inp("abbb.inp");
ofstream out("abbb.out");

int n;
string st;
void abbb(){
    inp >> st;
    
    for(int i=0;i<st.size();i++) {
        if(st.size() > i) {
            if((st[i] == 'A' && st[i+1] == 'B') || (st[i] == 'B' && st[i+1] == 'B')) {
                st.erase(st.begin()+i,st.begin()+i+2);
                if(i >= 1) {
                    i -=2;
                }
                else {
                    i--;
                }
            }
        }
    }
    
    out << st.size() << endl;
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        inp >> n;
        abbb();
    }
}
