#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

void dijkstra(int V, vector<Edge>& edges, int src) {
  
    vector<vector<pair<int,long long>>> graph(V);
    for (auto& e : edges) {
        graph[e.u].push_back({e.v, e.w});
        graph[e.v].push_back({e.u, e.w});
    }

    vector<long long> dist(V, LLONG_MAX);
    dist[src] = 0;

    using P = pair<long long,int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        P top = pq.top();
        pq.pop();
        long long d = top.first;
        int u = top.second;

        if (d > dist[u]) continue;

        for (auto& edge : graph[u]) {
            int v = edge.first;
            long long w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Najkratka distanca od pocetnata tocka " << src <<endl;
    for (int i = 0; i < V; i++) {
        if (dist[i] == LLONG_MAX)
            cout << i << ": INF\n";
        else
            cout << i << ": " << dist[i] << "\n";
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<Edge> edges(E);
    for (int i = 0; i < E; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }
    int src;
    cin >> src;
    dijkstra(V, edges, src);
}
