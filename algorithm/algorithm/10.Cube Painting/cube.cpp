#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream inp("cube.inp");
ofstream out("cube.out");

void rotation1(string &dice) {     //2->1 방향으로 회전
    string temp = dice;
    dice[0] = temp[1];
    dice[1] = temp[5];
    dice[5] = temp[4];
    dice[4] = temp[0];
}

void rotation2(string &dice) {   //3->2 방향으로 회전
    string temp = dice;
    dice[1] = temp[2];
    dice[2] = temp[4];
    dice[3] = temp[1];
    dice[4] = temp[3];
}

void rotation3(string &dice) {    //3->1 방향으로 회전
    string temp = dice;
    dice[0] = temp[2];
    dice[2] = temp[5];
    dice[5] = temp[3];
    dice[3] = temp[0];
}

bool compare_dice(string dice1, string dice2) {
    for(int i=0;i<4;i++) {
        rotation1(dice2);
        for(int j=0;j<4;j++) {
            rotation2(dice2);
            if(dice1 == dice2) return true;
        }
    }
    rotation3(dice2);
    for(int i=0;i<4;i++) {
        rotation1(dice2);
        for(int j=0;j<4;j++) {
            rotation2(dice2);
            if(dice1 == dice2) return true;
        }
    }
    
    return false;
}

int cube(){
    string input_st;
    inp >> input_st;
    
    string dice1,dice2;
    dice1 = input_st.substr(0,6);
    dice2 = input_st.substr(6,6);
    
    if(dice1 == dice2) {
        bool check = true;
        char com = dice1[0];
        for(int i=1;i<6;i++) {
            if(com != dice1[i]) {
                check = false;
            }
        }
        if(check) return -1;
        else return 1;
    }
    
    int r1=0,g1=0,b1=0;
    int r2=0,g2=0,b2=0;
    
    for(int i=0;i<6;i++) {
        if(dice1[i] == 'r') r1++;
        else if(dice1[i] == 'g') g1++;
        else b1++;
        
        if(dice2[i] == 'r') r2++;
        else if(dice2[i] == 'g') g2++;
        else b2++;
    }
    
    if(r1!=r2 || g1!=g2 || b1!=b2) return 0;
    
    if(compare_dice(dice1,dice2)){
        return 1;
    }
    else {
        return 0;
    }
}

int main(void) {
    while(1) {
        int check = cube();
        if(check == 0) {
            out << "FALSE" << endl;
        }
        else if(check == 1) {
            out << "TRUE" << endl;
        }
        else {
            out << "TRUE" << endl;
            break;
        }
    }
}
