#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <utility>
using  namespace std;

ifstream inp("watertank.inp");
ofstream out("watertank.out");

typedef struct {
    int i;
    int j;
    int h;
}Save_pq;

int N,M,H;
int hole[1003][1003][4];        //input
int water_depth[1003][1003];    //결과

class cmp {
public:
    bool operator()(const Save_pq &p1, const Save_pq &p2) const{
        if(p1.h > p2.h) return true;
        else return false;
    }
};

void input(){
    int temp;
    
    for(int i=1;i<=N+1;i++) {
        for(int j=1;j<=M;j++) {
            inp >> temp;
            hole[i-1][j][2] = temp;
            hole[i][j][0] = temp;
        }
    }
    
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M+1;j++) {
            inp >> temp;
            hole[i][j-1][1] = temp;
            hole[i][j][3] = temp;
        }
    }
    
    for(int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            water_depth[i][j] = H;
        }
    }
}

void watertank(){
    input();
    
    Save_pq temp;
    priority_queue<Save_pq, vector<Save_pq>, cmp> pq;
    
    for(int i=0;i<=M+1;i++) {
        if(hole[0][i][2] != -1) {
            water_depth[1][i] = hole[0][i][2];
            pq.push({1,i,hole[0][i][2]});
        }
        if(hole[N+1][i][0] != -1) {
            water_depth[N][i] = hole[N+1][i][0];
            pq.push({N,i,hole[N+1][i][0]});
        }
    }
    
    for(int i=0;i<=N+1;i++) {
        if(hole[i][0][1] != -1) {
            water_depth[i][1] = hole[i][0][1];
            pq.push({i,1,hole[i][0][1]});
        }
        if(hole[i][M+1][3] != -1) {
            water_depth[i][M] = hole[i][M+1][3];
            pq.push({i,M,hole[i][M+1][3]});
        }
    }
    
    while(pq.size()) {
        temp = pq.top();
        pq.pop();
        
        if(temp.h == water_depth[temp.i][temp.j]) {
            for(int i=0;i<4;i++) {
                if(hole[temp.i][temp.j][i] != -1) {
                    int nexti,nextj;
                    if(i == 0) {                //아래
                        nexti = temp.i + -1;
                        nextj = temp.j;
                    }
                    else if(i == 1) {           //오른쪽
                        nexti = temp.i;
                        nextj = temp.j + 1;
                    }
                    else if(i == 2) {           //위
                        nexti = temp.i + 1;
                        nextj = temp.j;
                    }
                    else {                      //왼쪽
                        nexti = temp.i;
                        nextj = temp.j + -1;
                    }
                    if(!(nexti < 1 || nextj < 1 || nexti > N || nextj > M)) {
                        int nexth = max(min(hole[temp.i][temp.j][i],  water_depth[nexti][nextj]),water_depth[temp.i][temp.j]);
                        if(water_depth[nexti][nextj] > nexth) {
                            water_depth[nexti][nextj] = nexth;
                            pq.push({nexti,nextj,nexth});
                        }
                    }
                }
            }
        }
    }
    
    int sum = 0;
    for (int i=1;i<=N;i++) {
        for(int j=1;j<=M;j++) {
            sum += water_depth[i][j];
        }
    }
    out << sum << endl;
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        inp >> N >> M >> H;
        watertank();
    }
}
