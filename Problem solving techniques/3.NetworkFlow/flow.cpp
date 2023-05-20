#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

ifstream inp("flow.inp");
ofstream out("flow.out");

struct Edge
{
    int to;
    int capacity;
    int flow;
    int rev;
};

const int INF = 1e9;

vector<vector<Edge>> graph;
vector<bool> visited;
vector<int> parent;

void addEdge(int from, int to, int capacity)
{
    graph[from].push_back({to, capacity, 0, static_cast<int>(graph[to].size())});
    graph[to].push_back({from, capacity, 0, static_cast<int>(graph[from].size()) - 1});
}

bool bfs(int source, int sink)
{
    fill(parent.begin(), parent.end(), -1);
    fill(visited.begin(), visited.end(), false);

    queue<int> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (auto &edge : graph[node])
        {
            int to = edge.to;
            if (!visited[to] && edge.capacity > edge.flow)
            {
                q.push(to);
                visited[to] = true;
                parent[to] = node;
            }
        }
    }

    return visited[sink];
}

int maxFlow(int source, int sink)
{
    int totalFlow = 0;

    while (bfs(source, sink))
    {
        int minFlow = INF;

        for (int node = sink; node != source; node = parent[node])
        {
            int prevNode = parent[node];
            for (auto &edge : graph[prevNode])
            {
                if (edge.to == node)
                {
                    minFlow = min(minFlow, edge.capacity - edge.flow);
                    break;
                }
            }
        }

        for (int node = sink; node != source; node = parent[node])
        {
            int prevNode = parent[node];
            for (auto &edge : graph[prevNode])
            {
                if (edge.to == node)
                {
                    edge.flow += minFlow;
                    graph[node][edge.rev].flow -= minFlow;
                    break;
                }
            }
        }

        totalFlow += minFlow;
    }

    return totalFlow;
}

int main()
{
    int n;
    inp >> n;

    graph.resize(n);
    visited.resize(n);
    parent.resize(n);

    while (true)
    {
        int from, to, capacity;
        inp >> from >> to >> capacity;
        if (from == -1 && to == -1 && capacity == -1)
            break;
        addEdge(from, to, capacity);
    }

    int source = 0;
    int sink = n - 1;

    int result = maxFlow(source, sink);

    out << result << endl;

    return 0;
}
