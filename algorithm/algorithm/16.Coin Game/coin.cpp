#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("coin.inp");
ofstream out("coin.out");

int bottle[3];
bool play_count[101][101][101]; //true = win, false = lose

bool win_check(int i, int j, int k){
    if(i-1>=0) {
        if(!play_count[i-1][j][k]) return true;
    }
    if(i-2>=0) {
        if(!play_count[i-2][j][k]) return true;
    }
    if(i-3>=0) {
        if(!play_count[i-3][j][k]) return true;
    }
    else {
        if(j-1>=0) {
            if(j-1<i) {
                if(!play_count[j-1][i][k]) return true;
            }
            else{
                if(!play_count[i][j-1][k]) return true;
            }
        }
        if(j-2>=0) {
            if(j-2<i) {
                if(!play_count[j-2][i][k]) return true;
            }
            else {
                if(!play_count[i][j-1][k]) return true;
            }
        }
        if(j-3>=0) {
            if(j-3<i) {
                if(!play_count[j-3][i][k]) return true;
            }
            else {
                if(!play_count[i][j-3][k]) return true;
            }
        }
        
        if(k-1>=0) {
            if(k-1<j) {
                if(k-1<i) {
                    if(!play_count[k-1][i][j]) return true;
                }
                else {
                    if(!play_count[i][k-1][j]) return true;
                }
            }
            else {
                if(!play_count[i][j][k-1]) return true;
            }
        }
        if(k-2>=0) {
            if(k-2<j) {
                if(k-2<i) {
                    if(!play_count[k-2][i][j]) return true;
                }
                else {
                    if(!play_count[i][k-2][j]) return true;
                }
            }
            else {
                if(!play_count[i][j][k-2]) return true;
            }
        }
        if(k-3>=0) {
            if(k-3<j) {
                if(k-3<i) {
                    if(!play_count[k-3][i][j]) return true;
                }
                else {
                    if(!play_count[i][k-3][j]) return true;
                }
            }
            else {
                if(!play_count[i][j][k-3]) return true;
            }
        }
    }
    return false;
}

void coin_cal(){
    play_count[0][0][0] = true;
    for(int i=0;i<=100;i++) {
        for(int j=i;j<=100;j++) {
            for(int k=j;k<=100;k++) {
                if(i==0&&j==0&&k==0) continue;
                play_count[i][j][k] = win_check(i,j,k);
            }
        }
    }
}

int main(void) {
    int n;
    inp >> n;
    
    coin_cal();
    
    for(int i=0;i<n;i++) {
        inp >> bottle[0] >> bottle[1] >> bottle[2];
        out << "(" << bottle[0] << " " << bottle[1] << " " << bottle[2] << ") : ";
        sort(bottle,bottle+3);
        if(play_count[bottle[0]][bottle[1]][bottle[2]]) {
            out << "1" << endl;
        }
        else {
            out << "-1" << endl;
        }
    }
}
