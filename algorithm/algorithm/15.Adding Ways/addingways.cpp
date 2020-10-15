#include <iostream>
#include <fstream>
using namespace std;

ifstream inp("addingways.inp");
ofstream out("addingways.out");

int n,k;

void addingways(){
    int arr[301][301] = { 0 };
    arr[1][1] = 1;
    arr[2][1] = 1;
    arr[2][2] = 1;
    for(int i=3;i<=n;i++) {
        for(int j=1;j<=i;j++) {
            if(j==1 || i==j) {
                arr[i][j] = 1;
            }
            else {
                int sum = 0;
                for(int k_temp=1;k_temp<=j;k_temp++) {
                    if(k_temp > (i-j)) {
                        break;
                    }
                    sum = ((arr[i-j][k_temp]%1000000007)+(sum%1000000007))%1000000007;
                }
                arr[i][j] = sum%1000000007;
            }
        }
    }
    out << arr[n][k] << endl;
}

int main(void) {
    while(1) {
        inp >> n >> k;
        if(n == 0 && k == 0) {
            break;
        }
        else {
            addingways();
        }
    }
}
