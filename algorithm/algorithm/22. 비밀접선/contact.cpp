#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

ifstream inp("contact.inp");
ofstream out("contact.out");

int N,M,K;
int **D, **P;   //플로이드 배열 필요한거만 저장할 것임
bool *check;    //다익스트라 실행 유무
vector<pair<int, int> > *e; //간선의 정보
vector<pair<int, int> > path;

void dijkstra(int start) {
    if(check[start] != true) {
        check[start] = true;
        
        D[start][start] = 0;
        priority_queue<pair<int, int> > pq;
        pq.push(make_pair(start, 0));
        
        while (!pq.empty()) {
            int current = pq.top().first;
            int distance = -pq.top().second;
            pq.pop();
            
            if(D[start][current] < distance) continue;
            for(int i=0;i<e[current].size();i++) {
                int next = e[current][i].first;
                int nextDistance = distance + e[current][i].second;
                if(nextDistance < D[start][next]) {
                    D[start][next] = nextDistance;
                    P[start][next] = current;
                    
                    pq.push(make_pair(next, -nextDistance));
                }
            }
        }
    }
}

void input() {
    e = new vector<pair<int, int> >[N+1];
    
    check = new bool[N+1];
    
    D = new int*[N+1];
    P = new int*[N+1];
    for (int i=0; i<N+1; i++) {
        D[i]=new int[N+1];
        P[i]=new int[N+1];
    }
    
    int INF = 1000000;
    
    for(int i=0;i<N+1;i++) {
        for (int j=0;j<N+1; j++) {
            D[i][j] = INF;
            P[i][j] = 0;
        }
    }
    
    int start, end, val;
    for(int i=0;i<M;i++) {
        inp >> start >> end >> val;
        e[start].push_back(make_pair(end, val));
        e[end].push_back(make_pair(start, val));
    }
}

void contact(){
    inp >> N >> M >> K;
    
    input();
    
    int v1, v2;
    for(int i=0;i<K;i++) {
        inp >> v1 >> v2;
        path.clear();
        if(!check[v1]) dijkstra(v1);
        if(!check[v2]) dijkstra(v2);
        
        for(int j=1;j<N+1;j++) {
            if(D[v1][v2] == D[v1][j]+D[v2][j]) {
                if(D[v1][j] > D[v2][j]) {
                    
                }
                else if(D[v1][j] == D[v2][j]) {
                    path.push_back(make_pair(j, j));
                }
                else {
                    int pre_node = v2;
                    int now_node = j;
                    int len = D[v1][v2]-D[v1][j];
                    
                    while(end != start){
                        end = P[v2][end];
                        
                    }
                }
            }
        }
    }
    
}

int main(void) {
    int T;
    inp >> T;
    
    for(int i=0;i<T;i++) {
        contact();
    }
}
