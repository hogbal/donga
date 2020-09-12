#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream inp("turtle.inp");
ofstream out("turtle.out");



int turtle(){
    string st;
    inp >> st;
    
    int h = 0;
    int v = 0;
    int h_max = 0;
    int v_max = 0;
    int h_min = 0;
    int v_min = 0;
    int direction = 0; //0 = 위, 1 = 아래, 2 = 왼쪽, 3 = 오른쪽
    
    for(int i=0;i<st.size();i++) {
        if(st[i] == 'F') {
            if(direction == 0) {
                h++;
                if(h > h_max) {
                    h_max = h;
                }
            }
            else if(direction == 1) {
                h--;
                if(h < h_min) {
                    h_min = h;
                }
            }
            else if(direction == 2) {
                v--;
                if(v < v_min) {
                    v_min = v;
                }
            }
            else if(direction == 3) {
                v++;
                if(v > v_max) {
                    v_max = v;
                }
            }
        }
        else if(st[i] == 'B') {
            if(direction == 0) {
                h--;
                if(h < h_min) {
                    h_min = h;
                }
            }
            else if(direction == 1) {
                h++;
                if(h > h_max) {
                    h_max = h;
                }
            }
            else if(direction == 2) {
                v++;
                if(v > v_max) {
                    v_max = v;
                }
            }
            else if(direction == 3) {
                v--;
                if(v < v_min) {
                    v_min = v;
                }
            }
        }
        else if(st[i] == 'L') {
            if(direction == 0) {
                direction = 2;
            }
            else if(direction == 1){
                direction = 3;
            }
            else if(direction == 2) {
                direction = 1;
            }
            else if(direction == 3) {
                direction = 0;
            }
        }
        else if(st[i] == 'R'){
            if(direction == 0) {
                direction = 3;
            }
            else if(direction == 1){
                direction = 2;
            }
            else if(direction == 2) {
                direction = 0;
            }
            else if(direction == 3) {
                direction = 1;
            }
        }
    }
    
    return (h_max - h_min) * (v_max - v_min);
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        out << turtle() << endl;
    }
}
