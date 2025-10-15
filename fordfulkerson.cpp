#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// BFS to find an augmenting path
int bfs(int source, int sink, vector<int>& parent, vector<vector<int>>& residualGraph) {
    fill(parent.begin(), parent.end(), -1);
    int V = residualGraph.size();
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, INT_MAX});

    while (!q.empty()) {
        int u = q.front().first;
        int capacity = q.front().second;
        q.pop();

        for (int av = 0; av < V; av++) {
            if (u != av && parent[av] == -1 && residualGraph[u][av] > 0) {
                parent[av] = u;
                int min_cap = min(capacity, residualGraph[u][av]);
                if (av == sink)
                    return min_cap;
                q.push({av, min_cap});
            }
        }
    }
    return 0;
}

// Ford-fulkerson algoritam
int ford_fulkerson(vector<vector<int>>& graph, int source, int sink) {
    int V = graph.size();
    vector<int> parent(V, -1);
    vector<vector<int>> residualGraph = graph;
    int max_flow = 0, min_cap;

    while ((min_cap = bfs(source, sink, parent, residualGraph))) {
        max_flow += min_cap;
        int u = sink;
        while (u != source) {
            cout<<u<<" ";
            int v = parent[u];
            residualGraph[v][u] -= min_cap;
            residualGraph[u][v] += min_cap;
            u = v;
        }
        cout<<min_cap;
        cout<<endl;
    }
    return max_flow;
}

int main() {
    int V, E;
    cin >> V;
    cin >> E;
    vector<vector<int>> graph(V, vector<int>(V, 0));
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u-1][v-1] = w;
    }

    int source, sink;
    cin >> source;
    cin >> sink;
    sink--;
    source--;
    cout << "Max flow: " << ford_fulkerson(graph, source, sink) << endl;
    return 0;
}
