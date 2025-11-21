#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int to;            
    int rev;          
    long long cap;   

   Edge(int _to, int _rev, long long _cap) {
    to = _to;
    rev = _rev;
    cap = _cap;
}

};

struct PushRelabel {
    int n;                                 
    vector<vector<Edge>> adj;              
    vector<long long> excess;              
    vector<int> height;                   

   PushRelabel(int n) {
    this->n = n;
    adj = vector<vector<Edge>>(n);
    excess = vector<long long>(n, 0);
    height = vector<int>(n, 0);
}


    void addEdge(int u, int v, long long cap) {
        adj[u].push_back(Edge(v, (int)adj[v].size(), cap));
        adj[v].push_back(Edge(u, (int)adj[u].size() - 1, 0));
    }

    void push(int u, Edge &e) {
        long long send = min(excess[u], e.cap);
        if (send == 0 || height[u] != height[e.to] + 1) return;
        e.cap -= send;
        adj[e.to][e.rev].cap += send;
        excess[u] -= send;
        excess[e.to] += send;
    }

    void relabel(int u) {
        int minh = INT_MAX;
        for (auto &e : adj[u]) {
            if (e.cap > 0) minh = min(minh, height[e.to]);
        }
        if (minh < INT_MAX) height[u] = minh + 1;
    }

    long long maxFlow(int s, int t) {
        height.assign(n, 0);
        excess.assign(n, 0);
        height[s] = n;

        for (auto &e : adj[s]) {
            if (e.cap > 0) {
                long long c = e.cap;
                e.cap = 0;
                adj[e.to][e.rev].cap += c;
                excess[e.to] += c;
            }
        }

        queue<int> Q;
        for (int i = 0; i < n; ++i)
            if (i != s && i != t && excess[i] > 0) Q.push(i);

        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            bool pushed_any = false;
            for (auto &e : adj[u]) {
                if (excess[u] == 0) break;
                long long before = excess[u];
                push(u, e);
                if (excess[u] < before) pushed_any = true;

                if (excess[e.to] > 0 && e.to != s && e.to != t) {
                }
            }
            if (excess[u] > 0) {
                relabel(u);
                Q.push(u);
            }
        }

        long long flow = 0;
        for (auto &e : adj[s]) flow += adj[e.to][e.rev].cap;
        return flow;
    }
};

int main() {

    int n, m;
    if (!(cin >> n >> m)) return 0;
    PushRelabel pr(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        pr.addEdge(u, v, c);
    }

    int s, t;
    cin >> s >> t;

    long long maxflow = pr.maxFlow(s, t);
    cout << maxflow << "\n";
    return 0;
}
