#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("coin.inp");
ofstream out("coin.out");

typedef struct {
    int b1[3];
    int b2[3];
    int b3[3];
    bool check;
}Coin;

Coin c[101][101][101];

bool find_win(int index, int arr[]) {
    for(int i=0;i<3;i++) {
        if(index == i) continue;
        if(c[arr[0]][arr[1]][arr[2]].b1[i] == 2) return true;
        if(c[arr[0]][arr[1]][arr[2]].b2[i] == 2) return true;
        if(c[arr[0]][arr[1]][arr[2]].b3[i] == 2) return true;
    }
    return false;
}

void cal(int i, int j, int k){
    for(int index=0;index<3;index++) {
        if(i-(index+1) >= 0) {
            int arr[3];
            arr[0] = i-(index+1);
            arr[1] = j;
            arr[2] = k;
            if(find_win(index,arr)) {
                c[i][j][k].b1[index] = 1;
            }
            else {
                c[i][j][k].b1[index] = 2;
            }
        }
    }
    
    for(int index=0;index<3;index++) {
        if(j-(index+1) >= 0){
            int arr[3];
            arr[0] = i;
            arr[1] = j-(index+1);
            arr[2] = k;
            sort(arr,arr+3);
            if(find_win(index,arr)) {
                c[i][j][k].b2[index] = 1;
            }
            else {
                c[i][j][k].b2[index] = 2;
            }
        }
    }
    
    for(int index=0;index<3;index++) {
        if(k-(index+1) >=0){
            int arr[3];
            arr[0] = i;
            arr[1] = j;
            arr[2] = k-(index+1);
            sort(arr,arr+3);
            if(find_win(index,arr)) {
                c[i][j][k].b3[index] = 1;
            }
            else {
                c[i][j][k].b3[index] = 2;
            }
        }
    }
}

void coin_cal(){
    c[0][0][1].b3[0] = 1;
    c[0][0][2].b3[0] = 2;
    c[0][0][2].b3[1] = 1;
    c[0][0][3].b3[0] = 2;
    c[0][0][3].b3[1] = 2;
    c[0][0][3].b3[2] = 1;
    
    c[0][0][0].check = true;
    c[0][0][1].check = true;
    c[0][0][2].check = true;
    c[0][0][3].check = true;
    
    for(int i=0;i<=100;i++) {
        for(int j=i;j<=100;j++) {
            for(int k=j;k<=100;k++) {
                if(c[i][j][k].check) continue;
                cal(i,j,k);
            }
        }
    }
}

int main(void) {
    int n;
    inp >> n;
    
    coin_cal();
    
    for(int i=0;i<n;i++) {
        int bottle[3];
        inp >> bottle[0] >> bottle[1] >> bottle[2];
        out << "(" << bottle[0] << " " << bottle[1] << " " << bottle[2] << ") : ";
        sort(bottle,bottle+3);
        bool check = false;
        for(int j=0;j<3;j++) {
            if(c[bottle[0]][bottle[1]][bottle[2]].b1[j] == 2) check = true;
            if(c[bottle[0]][bottle[1]][bottle[2]].b2[j] == 2) check = true;
            if(c[bottle[0]][bottle[1]][bottle[2]].b3[j] == 2) check = true;
        }
        if(check) {
            out << "1" << endl;
        }
        else {
            out << "-1" << endl;
        }
    }
}
