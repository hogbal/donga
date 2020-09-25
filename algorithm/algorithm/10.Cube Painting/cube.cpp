#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream inp("cube.inp");
ofstream out("cube.out");

void change_top(string &dice, int num, string dice_save) {
    if(num == 0) {
        return;
    }
    else if(num == 1){
        dice[0] = dice_save[1];
        dice[1] = dice_save[5];
        dice[5] = dice_save[4];
        dice[4] = dice_save[0];
    }
    else if(num == 2) {
        dice[0] = dice_save[2];
        dice[2] = dice_save[5];
        dice[5] = dice_save[3];
        dice[3] = dice_save[0];
    }
    else if(num == 3) {
        dice[0] = dice_save[3];
        dice[3] = dice_save[5];
        dice[5] = dice_save[2];
        dice[2] = dice_save[0];
    }
    else if(num == 4) {
        dice[0] = dice_save[4];
        dice[4] = dice_save[5];
        dice[5] = dice_save[1];
        dice[1] = dice_save[0];
    }
    else if(num == 5) {
        dice[0] = dice_save[5];
        dice[5] = dice_save[0];
        dice[1] = dice_save[4];
        dice[4] = dice_save[1];
    }
}

void rotation(string &dice) {
    string temp = dice;
    dice[1] = temp[2];
    dice[2] = temp[4];
    dice[3] = temp[1];
    dice[4] = temp[3];
}

bool compare_dice(string dice1, string dice2) {
    string dice2_save = dice2;
    for(int i=0;i<6;i++) {
        change_top(dice2,i,dice2_save);
        for(int j=0;j<4;j++) {
            rotation(dice2);
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
