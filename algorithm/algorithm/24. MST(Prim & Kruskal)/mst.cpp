#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

ifstream inp("mst.inp");
ofstream out("mst.out");

typedef struct {
    int u;
    int v;
    int w;
    int index;
}Edge;

int V,E;
int *check;
Edge *e;
vector<Edge> *ev;

bool cmp(const Edge &e1, const Edge &e2) {
    if(e1.w < e2.w) return true;
    else if(e1.w == e2.w){
        if(e1.index < e2.index) return true;
        else return false;
    }
    else {
        return false;
    }
}

int getParent(int node){
    if(check[node]==node) return node;
    return getParent(check[node]);
}

bool isCycle(int node1, int node2){
    node1 = getParent(node1);
    node2 = getParent(node2);
    if(node1==node2) return true;
    else return false;
}

void unionParent(int node1, int node2){
    node1 = getParent(node1);
    node2 = getParent(node2);
    if(node1<node2) check[node2] = node1;
    else check[node1] = node2;
}

void Kruskal(){
    sort(e,e+E,cmp);
    int *num = new int[V-1];
    check = new int[V];
    
    for(int i=0;i<V;i++) {
        check[i] = i;
    }
    
    int sum = 0;
    int index = 0;
    for(int i=0;i<E;i++){
        if(!isCycle(e[i].u, e[i].v)){
            sum+=e[i].w;
            num[index] = e[i].index;
            index++;
            unionParent(e[i].u, e[i].v);
        }
    }
    out << "Tree edges by Kruskal algorithm: " << sum << endl;
    for(int i=0;i<index;i++) {
        out << num[i] << endl;
    }
}

void Prim(int start_node){
    vector<pair<int, int> > selected;
    int *minw = new int[V];
    int *node_index = new int[V];
    int *parent = new int[V];
    bool *added = new bool[V];
    int *num = new int[V-1];
    for(int i=0;i<V;i++) {
        added[i] = false;
        minw[i] = 100000;
        parent[i] = -1;
        node_index[i] = -1;
        sort(ev[i].begin(), ev[i].end(),cmp);
    }
    
    int ret = 0;
    int index = 0;
    minw[start_node] = 0;
    parent[start_node] = start_node;
    
    for(int i=0;i<V;i++) {
        int u = -1;
        for(int v=0;v<V;v++) {
            if(!added[v] && (u == -1 || minw[u] >= minw[v])) {
                if(minw[u] != minw[v]) {
                    u = v;
                }
                else {
                    if(node_index[u] > node_index[v]) {
                        u = v;
                    }
                }
            }
        }
        
        if(parent[u] != u) {
            selected.push_back(make_pair(parent[u], u));
        }
        
        ret += minw[u];
        added[u] = true;
        if(node_index[u] != -1) {
            num[index] = node_index[u];
            index++;
        }
        
        for(int j=0;j<ev[u].size();j++) {
            int v = ev[u][j].v, w = ev[u][j].w;
            if(!added[v] && minw[v] > w) {
                parent[v] = u;
                minw[v] = w;
                node_index[v] = ev[u][j].index;
            }
        }
    }
    out << "Tree edges by Prim algorithm with starting vertex " << start_node << ": " << ret << endl;
    for(int i=0;i<index;i++) {
        out << num[i] << endl;
    }
}

int main(void) {
    inp >> V >> E;
    e = new Edge[E];
    ev = new vector<Edge>[E];
    for(int i=0;i<E;i++){
        int u, v, w;
        inp >> u >> v >> w;
        e[i].u = u; e[i].v = v; e[i].w = w;
        e[i].index = i;
        
        Edge temp;
        temp.v = v;
        temp.w = w;
        temp.index = i;
        ev[u].push_back(temp);
        temp.v = u;
        ev[v].push_back(temp);
    }
    Kruskal();
    Prim(0);
    Prim(V/2);
    Prim(V-1);
}
