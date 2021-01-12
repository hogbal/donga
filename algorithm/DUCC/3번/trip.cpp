#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("trip.inp");
ofstream out("trip.out");

int n;
void trip(){
    int result = 0;
    long long sum = 0;
    long long avg = 0;
    
    int *p = new int[n];
    for(int i=0;i<n;i++) {
        inp >> p[i];
        sum += p[i];
    }
    avg = sum/n;
    
    sort(p,p+n);
    
    int j = n-1;
    int i = 0;
    
    while(p[i] < avg) {
        long long give1 = avg - p[i];
        long long give2 = p[j] - (avg+1);
        if(give1 > give2) {
            p[i] += give2;
            p[j] -= give2;
            result += give2;
            j--;
        }
        else if(give1 == give2) {
            p[i] += give1;
            p[j] -= give1;
            result += give1;
            i++;
            j--;
        }
        else {
            p[i] += give1;
            p[j] -= give1;
            result += give1;
            i++;
        }
        if(i >= j) break;
        sort(p+i,p+j+1);
    }
    
    for(int i=0;i<n;i++) {
        if(p[i] > avg+1) {
            long long give = p[i] - (avg+1);
            result += give;
        }
        if(p[i] < avg) {
            long long give = avg - p[i];
            result += give;
        }
    }
    
    out << result << endl;
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        inp >> n;
        trip();
    }
}
