#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("coin.inp");
ofstream out("coin.out");

int bottle[3];
bool play_count[101][101][101]; //true = win, false = lose
int coin_count[101][101][101];

bool win_check(int i, int j, int k){
    if(i-1 >= 0) {
        if(!play_count[i-1][j][k] && coin_count[i-1][j][k] != 1) {
            coin_count[i][j][k] = 1;
            return true;
        }
    }
    if(i-2 >= 0) {
        if(!play_count[i-2][j][k] && coin_count[i-2][j][k] != 2) {
            coin_count[i][j][k] = 2;
            return true;
        }
    }
    if(i-3 >= 0) {
        if(!play_count[i-3][j][k] && coin_count[i-3][j][k] != 3) {
            coin_count[i][j][k] = 3;
            return true;
        }
    }
    
    if(j-1 >= 0) {
        if(!play_count[i][j-1][k] && coin_count[i][j-1][k] != 1) {
            coin_count[i][j][k] = 1;
            return true;
        }
    }
    if(j-2 >= 0) {
        if(!play_count[i][j-2][k] && coin_count[i][j-2][k] != 2) {
            coin_count[i][j][k] = 2;
            return true;
        }
    }
    if(j-3 >= 0) {
        if(!play_count[i][j-3][k] && coin_count[i][j-3][k] != 3) {
            coin_count[i][j][k] = 3;
            return true;
        }
    }
    
    if(k-1 >= 0) {
        if(!play_count[i][j][k-1] && coin_count[i][j][k-1] != 1) {
            coin_count[i][j][k] = 1;
            return true;
        }
    }
    if(k-2 >= 0) {
        if(!play_count[i][j][k-2] && coin_count[i][j][k-2] != 2) {
            coin_count[i][j][k] = 2;
            return true;
        }
    }
    if(k-3 >= 0) {
        if(!play_count[i][j][k-3] && coin_count[i][j][k-3] != 3) {
            coin_count[i][j][k] = 3;
            return true;
        }
    }
    
    coin_count[i][j][k] = -1;
    return false;
}

void coin_cal(){
    play_count[0][0][0] = true;
    coin_count[0][0][0] = -1;
    for(int i=0;i<=100;i++) {
        for(int j=0;j<=100;j++) {
            for(int k=0;k<=100;k++) {
                if(i==0&&j==0&&k==0) continue;
                if(coin_count[i][j][k] != 0) continue;
                play_count[i][j][k] = win_check(i,j,k);
                play_count[i][k][j] = play_count[i][j][k];
                play_count[j][i][k] = play_count[i][j][k];
                play_count[j][k][i] = play_count[i][j][k];
                play_count[k][i][j] = play_count[i][j][k];
                play_count[k][j][i] = play_count[i][j][k];
                
                coin_count[i][k][j] = coin_count[i][j][k];
                coin_count[j][i][k] = coin_count[i][j][k];
                coin_count[j][k][i] = coin_count[i][j][k];
                coin_count[k][i][j] = coin_count[i][j][k];
                coin_count[k][j][i] = coin_count[i][j][k];
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
