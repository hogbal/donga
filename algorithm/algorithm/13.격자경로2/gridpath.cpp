#include <iostream>
#include <fstream>
#include <stack>
#include <utility>
using namespace std;

ifstream inp("gridpath.inp");
ofstream out("gridpath.out");

void input_mat(int **mat, int n, int m){
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            inp >> mat[i][j];
        }
    }
}

void gridpath(int *cost[], int *mat[], int n, int m){
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(i==0 && j==0) {  //시작
                cost[i][j] = mat[i][j];
            }
            else if(mat[i][j] == -1) {  //현재 mat[i][j]가 -1인 경우
                cost[i][j] = -1;
            }
            else {  //나머지
                if(i == 0) {
                    if(cost[i][j-1] == -1) {
                        cost[i][j] = -1;
                    }
                    else {
                        cost[i][j] = mat[i][j] + cost[i][j-1];
                    }
                }
                else if(j == 0) {
                    if(cost[i-1][j] == -1) {
                        cost[i][j] = -1;
                    }
                    else {
                        cost[i][j] = mat[i][j] + cost[i-1][j];
                    }
                }
                else {
                    if(cost[i-1][j] == -1 && cost[i][j-1] == -1) {
                        cost[i][j] = -1;
                    }
                    else if(cost[i-1][j] == -1) {
                        cost[i][j] = mat[i][j]+cost[i][j-1];
                    }
                    else if(cost[i][j-1] == -1) {
                        cost[i][j] = mat[i][j]+cost[i-1][j];
                    }
                    else {
                        if(cost[i][j-1] > cost[i-1][j]) {
                            cost[i][j] = mat[i][j]+cost[i-1][j];
                        }
                        else {
                            cost[i][j] = mat[i][j]+cost[i][j-1];
                        }
                    }
                }
            }
        }
    }
    if(cost[n-1][m-1] == -1) {
        out << "No path." << endl;
    }
    else {
        out << cost[n-1][m-1] << endl;
        int index_i = n-1, index_j = m-1;
        stack<pair<int, int> > s;
        while(1) {
            if(index_i == 0 && index_j == 0) {
                s.push(make_pair(0,0));
                break;
            }
            else {
                s.push(make_pair(index_i, index_j));
                if(index_i == 0) {
                    index_j--;
                }
                else if(index_j == 0) {
                    index_i--;
                }
                else {
                    if(cost[index_i][index_j-1] == -1) {
                        index_i--;
                    }
                    else if(cost[index_i-1][index_j] == -1) {
                        index_j--;
                    }
                    else if(cost[index_i][index_j-1] >= cost[index_i-1][index_j]){
                        index_i--;
                    }
                    else {
                        index_j--;
                    }
                }
            }
        }
        while(!s.empty()) {
            out << "(" << s.top().first << " " << s.top().second << ")" << endl;
            s.pop();
        }
    }
}

int main(void) {
    int n,m;
    inp >> n >> m;
    int **mat;
    int **cost;
    mat = new int*[n];
    cost = new int*[n];
    for(int i=0;i<n;i++) {
        mat[i] = new int[m];
        cost[i] = new int[m];
    }
    input_mat(mat,n,m);
    gridpath(cost,mat,n,m);
}
