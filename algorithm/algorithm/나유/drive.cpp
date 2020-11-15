#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

ifstream inp("contact.inp");
ofstream out("contact.out");

int **D;
int **P;
int N,M,K;

float full_len;
float len;
bool check;
vector<pair<int, int> > path;

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
    if(a.first < b.first) return true;
    if(a.first == b.first) return a.second < b.second;
    else return false;
}

void input(){
    inp >> N >> M >> K;
    
    D = new int*[N+1];
    P = new int*[N+1];
    for(int i=1;i<N+1;i++) {
        D[i] = new int[N+1];
        P[i] = new int[N+1];
        for(int j=1;j<N+1;j++) {
            if(i == j) {
                D[i][j] = 0;
            }
            else {
                D[i][j] = 100000;
            }
            P[i][j] = 0;
        }
    }
    
    int start, end, value;
    for(int i=0;i<M;i++) {
        inp >> start >> end >> value;
        if(start == end) continue;
        D[start][end] = value;
        D[end][start] = value;
    }
}

void floyd(){
    input();
    
    for(int k=1;k<N+1;k++) {
        for(int i=1;i<N+1;i++) {
            for(int j=1;j<N+1;j++) {
                if(D[i][k] + D[k][j] < D[i][j]) {
                    P[i][j] = k;
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}

void path_find(int v1, int v2) {
    if(check) {
        if (P[v1][v2] != 0) {
            if(check) path_find(v1,P[v1][v2]);
            if(check) path_find(P[v1][v2],v2);
        }
        else {
            len += D[v1][v2];
            if(full_len/2 <= len && check) {
                check = false;
                if(v1 < v2) {
                    path.push_back(make_pair(v1, v2));
                }
                else {
                    path.push_back(make_pair(v2, v1));
                }
            }
        }
    }
}

void contact(){
    floyd();
    
    int v1,v2;
    for(int i=0;i<K;i++) {
        path.clear();
        inp >> v1 >> v2;
        
        for(int j=1;j<N+1;j++) {
            full_len = D[v1][v2];
            
            if(full_len == D[v1][j]+D[v2][j]) {
                check = true;
                if(D[v1][j] > D[v2][j]) {
                    len = D[v2][j];
                    path_find(j, v1);
                }
                else if(D[v1][j] == D[v2][j]) {
                    path.push_back(make_pair(j, j));
                }
                else {
                    len = D[v1][j];
                    path_find(j, v2);
                }
            }
        }
        
        sort(path.begin(),path.end(),cmp);
        out << path[0].first << " " << path[0].second << endl;
    }
    
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        contact();
    }
}
