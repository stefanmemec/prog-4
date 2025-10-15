#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int n;
vector<vector<int>> cap;
vector<vector<int>> adj;
int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int,int>> q;
    q.push({s, INF});
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (int nxt : adj[cur]) {
            if (parent[nxt] == -1 && cap[cur][nxt] > 0) {
                parent[nxt] = cur;
                int new_flow = min(flow, cap[cur][nxt]);
                if (nxt == t)
                    return new_flow;
                q.push({nxt, new_flow});
            }
        }
    }
    return 0;
}
int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n + 1);
    while (true) {
        int pushed = bfs(s, t, parent);
        if (pushed == 0)
            break;
        vector<int> path;
        int cur = t;
        while (cur != s) {
            path.push_back(cur);
            cur = parent[cur];
        }
        path.push_back(s);
        reverse(path.begin(), path.end());
        for (int i = 0; i < (int)path.size(); ++i) {
            if (i) cout << "-";
            cout << path[i];
        }
        cout << " | butnato "<<pushed<<"\n";
        cur = t;
        while (cur != s) {
            int prev = parent[cur];
            cap[prev][cur] -= pushed;
            cap[cur][prev] += pushed;
            cur = prev;
        }
        flow += pushed;
    }
    return flow;
}
void smenet_flow(int s, int t,int result) {
    vector<vector<int>> orgcap = cap;
    vector<int> vis(n + 1, 0);
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!vis[v] && cap[u][v] > 0) {
                vis[v] = 1;
                q.push(v);
            }
        }
    }
    int bu = -1, bv = -1, bcap = -1;
    for (int u = 1; u <= n; ++u) {
        if (!vis[u]) continue;
        for (int v : adj[u]) {
            if (vis[v]) continue;
            int orig = cap[u][v] + cap[v][u];
            if (orig > bcap) {
                bcap = orig;
                bu = u;
                bv = v;
            }
        }
    }
    cout <<bu << " -> " << bv<<" " << bcap << "\n";
    cout<<result-bcap;
}
int main() {
    int m;
    cin>>n>>m;
    cap.assign(n + 1, vector<int>(n + 1, 0));
    adj.assign(n + 1, vector<int>());
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin>>u>> v >> c;
        cap[u][v] += c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int s=1, t=n;
    int result = maxflow(s, t);
    cout << "max flow = " << result << "\n";
    smenet_flow(s,t,result);
    return 0;
}