#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("sum.inp");
ofstream out("sum.out");

int n, W;
int num[201];
int count_sum;
int sum;

void input(){
    sum = 0;
    
    for(int i=0;i<n;i++) {
        inp >> num[i];
        sum += num[i];
    }
    sort(num,num+n);
}

void sum_of_subset(int i, int val, int remainder) {
    if(val+remainder >= W && i < n && (W==val || val+num[i+1] <= W)) {
        if(W==val) {
            count_sum++;
        }
        else {
            sum_of_subset(i+1, val+num[i+1], remainder-num[i+1]);   //선택
            sum_of_subset(i+1, val, remainder-num[i+1]);            //선택안함
        }
    }
}

void cal(){
    input();
    count_sum = 0;
    sum_of_subset(-1, 0, sum);
    
    out << count_sum%100000 << endl;
}

int main(void) {
    int T;
    inp >> T;
    for(int i=0;i<T;i++) {
        inp >> n >> W;
        cal();
    }
}
