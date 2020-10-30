#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("cube.inp");
ofstream out("cube.out");

int W,L,H;
int cube[201][201][201];

int minW_cal(int cube_W, int cube_L, int cube_H){
    int min_val = 200000000;
    for(int w_left=1;w_left<=cube_W/2;w_left++) {
        min_val = min(min_val,cube[w_left][cube_L][cube_H] + cube[cube_W-w_left][cube_L][cube_H]);
    }
    return min_val;
}

int minL_cal(int cube_W, int cube_L, int cube_H){
    int min_val = 200000000;
    for(int l_left=1;l_left<=cube_L/2;l_left++) {
        min_val = min(min_val,cube[cube_W][l_left][cube_H] + cube[cube_W][cube_L-l_left][cube_H]);
    }
    return min_val;
}

int minH_cal(int cube_W, int cube_L, int cube_H){
    int min_val = 200000000;
    for(int h_left=1;h_left<=cube_H/2;h_left++) {
        min_val = min(min_val,cube[cube_W][cube_L][h_left] + cube[cube_W][cube_L][cube_H-h_left]);
    }
    return min_val;
}
void cube_cal(){
    for(int cube_W=1;cube_W<201;cube_W++) {
        for(int cube_L=1;cube_L<201;cube_L++) {
            for(int cube_H=1;cube_H<201;cube_H++) {
                if(cube[cube_W][cube_L][cube_H] == 0) {
                    if(cube_W == 1 || cube_L == 1 || cube_H == 1) {
                        cube[cube_W][cube_L][cube_H] = cube_W*cube_L*cube_H;
                    }
                    else if (cube_W % cube_H == 0 && cube_L % cube_H == 0) {
                        cube[cube_W][cube_L][cube_H] = (cube_W / cube_H) * (cube_L / cube_H);
                    }
                    else if (cube_W % cube_L == 0 && cube_H % cube_L == 0) {
                        cube[cube_W][cube_L][cube_H] = (cube_W / cube_L) * (cube_H / cube_L);
                    }
                    else if (cube_L % cube_W == 0 && cube_H % cube_W == 0) {
                        cube[cube_W][cube_L][cube_H] = (cube_L / cube_W) * (cube_H / cube_W);
                    }
                    else {
                        int min_w = minW_cal(cube_W,cube_L,cube_H);
                        int min_l = minL_cal(cube_W,cube_L,cube_H);
                        int min_h = minH_cal(cube_W,cube_L,cube_H);
                        int input_min = min(min_w,min_l);
                        cube[cube_W][cube_L][cube_H] = min(input_min,min_h);
                        
                        cube[cube_W][cube_H][cube_L] = cube[cube_W][cube_L][cube_H];
                        cube[cube_L][cube_W][cube_H] = cube[cube_W][cube_L][cube_H];
                        cube[cube_L][cube_H][cube_W] = cube[cube_W][cube_L][cube_H];
                        cube[cube_H][cube_W][cube_L] = cube[cube_W][cube_L][cube_H];
                        cube[cube_H][cube_L][cube_W] = cube[cube_W][cube_L][cube_H];
                    }
                }
            }
        }
    }
}

int main(void) {
    int T;
    inp >> T;
    
    cube_cal();
    for(int i=0;i<T;i++) {
        inp >> W >> L >> H;
        out << cube[W][L][H] << endl;
    }
}
