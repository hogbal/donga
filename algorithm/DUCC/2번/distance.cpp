#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream inp("distance.inp");
ofstream out("distance.out");

typedef struct {
    int val;
    vector<int> index;
}Arr;

int n;

bool cmp_val(const Arr &a1, const Arr &a2) {
    if(a1.val < a2.val) return true;
    else if(a1.val == a2.val) return a1.index[0] < a2.index[0];
    else return false;
}

void distance(){
    vector<Arr> a;
    
    for(int i=0;i<n;i++) {
        Arr temp;
        inp >> temp.val;
        temp.index.push_back(i+1);
        a.push_back(temp);
    }
    
    sort(a.begin(),a.end(),cmp_val);
    
    for(int i=0;i<a.size();i++) {
        if(a.size()-1 > i) {
            if(a[i].val == a[i+1].val) {
                for(int j=0;j<a[i+1].index.size();j++) {
                    a[i].index.push_back(a[i+1].index[j]);
                }
                a.erase(a.begin()+i+1);
                i--;
            }
        }
    }
    if(a.size() == 1) {
        out << "0" << endl;
    }
    else {
        int min_val = 100000;
        for(int i=0;i<a[0].index.size();i++) {
            for(int j=0;j<a[a.size()-1].index.size();j++) {
                int temp = a[0].index[i] - a[a.size()-1].index[j];
                if(temp < 0) {
                    temp = 0-temp;
                }
                min_val = min(min_val, temp);
            }
        }
        out << min_val << endl;
    }
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        inp >> n;
        distance();
    }
}
