#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("stickers.inp");
ofstream out("stickers.out");

int stickers(int *arr_st[2], int n){
    int result;
    int *arr_max[2];
    
    arr_max[0] = new int[n];
    arr_max[1] = new int[n];
    
    arr_max[0][0] = arr_st[0][0];
    arr_max[1][0] = arr_st[1][0];
    
    for(int i=1;i<n;i++) {
        arr_max[0][i] = max(arr_max[1][i-2],arr_max[1][i-1]) + arr_st[0][i];
        arr_max[1][i] = max(arr_max[0][i-2],arr_max[0][i-1]) + arr_st[1][i];
    }
    
    result = max(arr_max[0][n-1],arr_max[1][n-1]);
    
    return result;
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        int n;
        int *arr_st[2];
        inp >> n;
        
        arr_st[0] = new int[n];
        arr_st[1] = new int[n];
        
        for(int i=0;i<n;i++) {
            inp >> arr_st[0][i];
        }
        for(int i=0;i<n;i++) {
            inp >> arr_st[1][i];
        }
        out << stickers(arr_st,n) << endl;
    }
}
