#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

ifstream inp("polygon.inp");
ofstream out("polygon.out");

vector<int> failure_function(vector<int> s) {
    vector<int> p(s.size());
    int k = 0;
    for (int i = 1; i < s.size(); i++) {
        while (k > 0 && s[k] != s[i])
            k = p[k - 1];
        if (s[k] == s[i])
            ++k;
        p[i] = k;
    }
    return p;
}

int kmp(vector<int> s, vector<int> pattern) {
    int m = pattern.size();
    if (m == 0)
        return 0;
    vector<int> p = failure_function(pattern);
    for (int i = 0, k = 0; i < s.size(); i++)
        for (;; k = p[k - 1]) {
            if (pattern[k] == s[i]) {
                if (++k == m)
                    return i + 1 - m;
                break;
            }
            if (k == 0)
                break;
        }
    return -1;
}

void polygon(int N){
    vector<int> v1(N);
    vector<int> v2(N);
    vector<int> v3(N*2);
    
    for(int i=0;i<N;i++) {
        inp >> v1[i];
    }
    for(int i=0;i<N;i++) {
        inp >> v2[i];
    }
    //입력 끝!
    
    copy(v1.begin(),v1.end(),v3.begin());
    copy(v1.begin(),v1.end(),v3.begin()+v1.size());
    
    if(kmp(v3, v2) == -1) { //일치하지 않으면
        int end = v1.size()-1;
        for(int i=0;i<N;i++) {
            v3[i] = abs(v1[end]);
            if(end != 0) {
                if(v1[end-1] > 0) v3[i] = -v3[i];
            }
            else {
                if(v1[v1.size()-1] > 0) v3[i] = -v3[i];
            }
            v3[i+v1.size()] = v3[i];
            end--;
        }
        if(kmp(v3, v2) == -1) {
            out << "0" << endl;
        }
        else {
            out << "1" << endl;
        }
    }
    else {  //일치하면
        out << "1" << endl;
    }
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        int N;
        inp >> N;
        polygon(N);
    }
}
