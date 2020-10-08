#include <iostream>
#include <fstream>
#include <stack>
#include <utility>
using namespace std;

ifstream inp("path.inp");
ofstream out("path.out");

int M,N,K;

typedef struct {
    int num;
    int *cost;
    int *num_case;
    int M_w;
    int N_w;
}Edge;

void input_mat(Edge *e[]) {    //입력받는 함수
    int index_i,index_j;
    int temp;
    for(int i=0;i<K;i++) {
        inp >> index_i >> index_j;
        e[index_i][index_j].num = -1;
    }
    
    for(int i=0;i<M;i++) {
        for(int j=0;j<N-1;j++) {
            inp >> temp;
            e[i][j].N_w = temp;
        }
    }
    
    for(int i=0;i<M-1;i++) {
        for(int j=0;j<N;j++) {
            inp >> temp;
            e[i][j].M_w = temp;
        }
    }
}

void w_cal(Edge *e[], int index_i, int index_j){
    if(index_i == 0 && index_j == 0) {  //시작점은 가중치가 없음, 따라서 0 그대로
        e[index_i][index_j].cost[0] = 0;
    }
    else if(index_i == 0 && index_j == 1) { //[0,1]일 경우 [0,0]의 N_w값만 더해주면 된다.
        if(e[0][0].num != -1) {
            e[index_i][index_j].cost[0] = e[0][0].N_w;
        }
        else {
            e[index_i][index_j].cost[1] = e[0][0].N_w;
        }
    }
    else if(index_i == 1 && index_j == 0) { //[1,0]일 경우 [0,0]의 M_w값만 더해주면 된다.
        if(e[0][0].num != -1) {
            e[index_i][index_j].cost[0] = e[0][0].M_w;
        }
        else {
            e[index_i][index_j].cost[1] = e[0][0].M_w;
        }
    }
    else if(index_i == 0) { //맨 윗 줄일 경우 왼쪽 노드의 N_w값을 더해주면 된다.
        for(int i=0;i<M+N;i++) {
            if(e[index_i][index_j-1].cost[i] == 0) {
                e[index_i][index_j].cost[i] = 0;
            }
            else {
                e[index_i][index_j].cost[i] = e[index_i][index_j-1].N_w + e[index_i][index_j-1].cost[i];
            }
        }
    }
    else if(index_j == 0) { //맨 왼쪽 줄일 경우 윗 노드의 M_w값을 더해주면 된다.
        for(int i=0;i<M+N;i++) {
            if(e[index_i-1][index_j].cost[i] == 0) {
                e[index_i][index_j].cost[i] = 0;
            }
            else {
                e[index_i][index_j].cost[i] = e[index_i-1][index_j].M_w + e[index_i-1][index_j].cost[i];
            }
        }
    }
    else { //정석대로 계산 가중치값(M_w||N_w + cost)이 더 작은 값으로 할당 받으면 된다.
        for(int i=0;i<M+N;i++) {
            if(e[index_i-1][index_j].cost[i] == 0 && e[index_i][index_j-1].cost[i] == 0) {  //둘다 0 인경우 0을 할당
                e[index_i][index_j].cost[i] = 0;
            }
            else if(e[index_i-1][index_j].cost[i] == 0) {   //한 곳이 0일경우 다른 한곳의 값을 이용
                e[index_i][index_j].cost[i] = e[index_i][index_j-1].N_w + e[index_i][index_j-1].cost[i];
            }
            else if(e[index_i][index_j-1].cost[i] == 0) {   //한 곳이 0일경우 다른 한곳의 값을 이용
                e[index_i][index_j].cost[i] = e[index_i-1][index_j].M_w + e[index_i-1][index_j].cost[i];
            }
            else { //왼쪽노드와 윗 노드의 가중치를 계산해 더 작은 값으로 할당한다.
                if(e[index_i][index_j-1].cost[i]+e[index_i][index_j-1].N_w > e[index_i-1][index_j].cost[i]+e[index_i-1][index_j].M_w) {
                    e[index_i][index_j].cost[i] = e[index_i-1][index_j].M_w + e[index_i-1][index_j].cost[i];
                }
                else {
                    e[index_i][index_j].cost[i] = e[index_i][index_j-1].N_w + e[index_i][index_j-1].cost[i];
                }
            }
        }
    }
}

void case_cal(Edge *e[], int index_i, int index_j){
    if(index_i == 0 && index_j == 0) {      //시작점은 경우의수가 1
        e[index_i][index_j].num_case[0] = 1;
    }
    else if(index_i == 0) { //맨 윗줄일 경우 왼쪽 경우의수 그대로 가져옴.
        for(int i=0;i<M+N;i++) {
            e[index_i][index_j].num_case[i] = (e[index_i][index_j-1].num_case[i] % 100000);
        }
    }
    else if(index_j == 0) {
        for(int i=0;i<M+N;i++) { //맨 왼쪽줄일 경우 위 노트의 경우의수 그대로 가져옴.
            e[index_i][index_j].num_case[i] = (e[index_i-1][index_j].num_case[i] % 100000);
        }
    }
    else {
        for(int i=0;i<M+N;i++) { //왼쪽 + 위 노드 경우의수
            e[index_i][index_j].num_case[i] = ((e[index_i-1][index_j].num_case[i] % 100000) + (e[index_i][index_j-1].num_case[i] % 100000)) % 100000;
        }
    }
}

void arr_slide(Edge *e[], int index_i, int index_j){ //노드가 num==-1일 경우 가중치값과 경우의수 값을 한칸씩 미루고 [0]을 0으로 채움
    for(int i=M+N-1;i>=0;i--) {
        if(i == 0) {
            e[index_i][index_j].num_case[0] = 0;
            e[index_i][index_j].cost[0] = 0;
        }
        else {
            e[index_i][index_j].num_case[i] = e[index_i][index_j].num_case[i-1];
            e[index_i][index_j].cost[i] = e[index_i][index_j].cost[i-1];
        }
    }
}

void out_stack(Edge *e[], int k){
    int index_i = M-1, index_j = N-1;
    stack<pair<int, int> > v;
    int k_com = k;
    
    while(1) {
        if(index_i == 0 && index_j == 0) {
            v.push(make_pair(0,0));
            break;
        }
        else {
            v.push(make_pair(index_i, index_j));
            if(index_i == 0) {
                index_j--;
            }
            else if(index_j == 0) {
                index_i--;
            }
            else {
                if(e[index_i-1][index_j].cost[k] == 0) {
                    index_j--;
                }
                else if(e[index_i][index_j-1].cost[k] == 0) {
                    index_i--;
                }
                else if(e[index_i-1][index_j].cost[k] > e[index_i][index_j-1].cost[k]){
                    if(e[index_i][index_j-1].N_w+e[index_i][index_j-1].cost[k] != e[index_i][index_j].cost[k_com]) {
                        index_i--;
                    }
                    else {
                        index_j--;
                    }
                }
                else if(e[index_i-1][index_j].cost[k] == e[index_i][index_j-1].cost[k]){
                    if(e[index_i-1][index_j].M_w+e[index_i-1][index_j].cost[k] != e[index_i][index_j].cost[k_com]) {
                        index_j--;
                    }
                    else if(e[index_i][index_j-1].N_w+e[index_i][index_j-1].cost[k] != e[index_i][index_j].cost[k_com]) {
                        index_i--;
                    }
                    else {
                        index_j--;
                    }
                }
                else {
                    if(e[index_i-1][index_j].M_w+e[index_i-1][index_j].cost[k] != e[index_i][index_j].cost[k_com]) {
                        index_j--;
                    }
                    else {
                        index_i--;
                    }
                }
            }
            
            if(e[index_i][index_j].num == -1) {
                k--;
            }
            if(e[v.top().first][v.top().second].num == -1) {
                k_com--;
            }
        }
    }
    
    while(!v.empty()) {
        out << "(" << v.top().first << "," << v.top().second << ")";
        v.pop();
        if(!v.empty()) {
            out << "->";
        }
    }
    out << endl;
}

void path(Edge *e[]){
    for(int i=0;i<M;i++) {
        for(int j=0;j<N;j++) {
            w_cal(e,i,j);
            case_cal(e,i,j);
            if(e[i][j].num == -1) {
                arr_slide(e,i,j);
            }
            cout << "cost : ";
            for(int k=0;k<M+N;k++) {
                cout << " " << e[i][j].cost[k];
            }
            cout << endl;
            
            cout << "case : ";
            for(int k=0;k<M+N;k++) {
                cout << " " << e[i][j].num_case[k];
            }
            cout << endl;
            cout << endl;
        }
    }
    for(int i=0;i<M+N;i++) {
        if(e[M-1][N-1].num_case[i] != 0) {
            out << "k:" << i << " count:" << e[M-1][N-1].num_case[i] << " cost:" << e[M-1][N-1].cost[i] << endl;
            out_stack(e,i);
        }
    }
}

int main(void) {
    int C;
    
    inp >> C;
    for(int i=0;i<C;i++) {
        out << "Test Case No:" << i+1 << endl;
        inp >> M >> N >> K;
        
        Edge **e;
        e = new Edge*[M];
        for(int i=0;i<M;i++) {
            e[i] = new Edge[N];
        }
        for(int i=0;i<M;i++) {
            for(int j=0;j<N;j++) {
                e[i][j].num = 0;
                e[i][j].cost = new int[M+N];
                e[i][j].num_case = new int[M+N];
                for(int k=0;k<M+N;k++) {
                    e[i][j].cost[k] = 0;
                    e[i][j].num_case[k] = 0;
                }
            }
        }
        
        input_mat(e);
        path(e);
        out << endl;
    }
}
