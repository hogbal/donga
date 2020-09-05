#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream inp ("sequence.inp");
ofstream out ("sequence.out");

void sequence(vector<int> S, vector<int> C, vector<int> R, int n) {
    sort(S.begin(),S.end());
    R.resize(n);
    
    for(int i=n-1;i>=0;i--) {
        R[i] = S[C[i]];
        S.erase(S.begin()+C[i]);
    }
    
    for(int i=0;i<n;i++) {
        out << R[i] << endl;
    }
}

int main(void) {
    vector<int> S;
    vector<int> C;
    vector<int> R;
    int n;
    
    inp >> n;
    for(int i=0;i<n;i++) {
        int temp;
        inp >> temp;
        S.push_back(temp);
    }
    
    for(int i=0;i<n;i++) {
        int temp;
        inp >> temp;
        C.push_back(temp);
    }
    sequence(S, C, R, n);
}
