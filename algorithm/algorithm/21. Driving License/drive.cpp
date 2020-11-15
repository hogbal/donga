#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

ifstream inp("drive.inp");
ofstream out("drive.out");

int M,N,L,G;

typedef struct {
    int under_w;
    int right_w;
    int rotation[2][201];
}Edge;

Edge e[100][100];

void input_drive(){
    for(int i=0;i<M;i++) {
        for(int j=0;j<N-1;j++) {
            inp >> e[i][j].right_w;
        }
    }
    
    for(int i=0;i<M-1;i++) {
        for(int j=0;j<N;j++) {
            inp >> e[i][j].under_w;
        }
    }
}

void drive(){
    input_drive();
    
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            for(int k=0;k<201;k++) {
                for(int direction = 0;direction<2;direction++) {
                    e[i][j].rotation[direction][k] = G+1;
                }
            }
        }
    }
    
    e[0][0].rotation[0][0] = 0;
    e[0][0].rotation[1][0] = 0;
    
    int min_result = 200000000;
    
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            for(int k=0;k<201;k++) {
                for(int direction = 0;direction<2;direction++) {
                    if(e[i][j].rotation[direction][k] < G+1) {
                        if(i == M-1 && j == N-1) {  //마지막 Edge일 경우 최소값 계산
                            min_result = min(min_result,k);
                        }
                        if(k < 200) {
                            e[i][j].rotation[!direction][k+1] = min(e[i][j].rotation[!direction][k+1],e[i][j].rotation[direction][k]);
                        }
                        if (direction == 1){    //오른쪽 Edge 계산
                            if(j+1 < N) {
                                e[i][j+1].rotation[direction][k] = min(e[i][j+1].rotation[direction][k],e[i][j].rotation[direction][k]+e[i][j].right_w);
                            }
                        }
                        else{   //아래 Edge 계산
                            if(i+1 < M) {
                                e[i+1][j].rotation[direction][k] = min(e[i+1][j].rotation[direction][k],e[i][j].rotation[direction][k]+e[i][j].under_w);
                            }
                        }
                    }
                }
            }
        }
    }

    if(min_result != 200000000) out << (N+M-2)*L+min_result << endl;
    else out << "-1" << endl;
}

int main(void){
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        inp >> M >> N >> L >> G;
        drive();
    }
}
