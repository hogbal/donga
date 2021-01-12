#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

ifstream inp("numbers.inp");
ofstream out("numbers.out");

int n;
int T_count;

void numbers(){
    out << "Test Case #" << T_count << " : ";
    
    vector<int> num;
    for(int i=0;i<n;i++) {
        int temp;
        inp >> temp;
        num.push_back(temp);
    }
    sort(num.begin(),num.end());
    
    int result = num[n-2]-num[1];
    if(result > 0) {
        out << result << endl;
    }
    else {
        result = -result;
        out << result << endl;
    }
}

int main(void) {
    int T;
    inp >> T;
    T_count = 0;
    
    for(int i=0;i<T;i++) {
        inp >> n;
        T_count++;
        numbers();
    }
}
