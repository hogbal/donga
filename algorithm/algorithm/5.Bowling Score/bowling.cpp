#include <iostream>
#include <fstream>
using namespace std;

ifstream inp("bowling.inp");
ofstream out("bowling.out");

typedef struct{
    int s1;
    int s2;
    int s3;
}Bow;

int bowling(){
    int score = 0;
    
    Bow b[10];
    
    for(int i=0;i<10;i++) {
        if(i != 9) {
            inp >> b[i].s1;
            if(b[i].s1 != 10) {
                inp >> b[i].s2;
                b[i].s3 = 0;
            }
            else {
                b[i].s2 = 0;
                b[i].s3 = 0;
            }
        }
        else {
            inp >> b[i].s1;
            inp >> b[i].s2;
            if(b[i].s1 + b[i].s2 >= 10) {
                inp >> b[i].s3;
            }
            else {
                b[i].s3 = 0;
            }
        }
    }
    
    for(int i=0;i<10;i++) {
        if(i < 8) {
            score += b[i].s1;
            if(b[i].s1 == 10) {
                score += b[i+1].s1;
                if(b[i+1].s1 == 10) {
                    score += b[i+2].s1;
                }
                else {
                    score += b[i+1].s2;
                }
            }
            else {
                score += b[i].s2;
                if(b[i].s1 + b[i].s2 == 10) {
                    score += b[i+1].s1;
                }
            }
        }
        else if(i == 8) {
            score += b[i].s1;
            if(b[i].s1 == 10) {
                score += b[i+1].s1;
                score += b[i+1].s2;
            }
            else {
                score += b[i].s2;
                if(b[i].s1 + b[i].s2 == 10) {
                    score += b[i+1].s1;
                }
            }
        }
        else {
            score += b[i].s1;
            score += b[i].s2;
            if(b[i].s1 + b[i].s2 >= 10) {
                score += b[i].s3;
            }
        }
    }
    
    return score;
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++){
        out << bowling() << endl;
    }
}
