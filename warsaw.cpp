#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e15;

struct Edge { int u,v; ll w; };

int main() {
    int n,m; ll L;
    cin >> n >> m >> L;
    vector<Edge> edges(m);
    vector<vector<pair<int,ll>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v; ll w; cin >> u >> v >> w;
        u--; v--;
        edges[i] = {u,v,w};
        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    auto all_pairs = [&](vector<vector<pair<int,ll>>> &graph){
        vector<vector<ll>> dist(n, vector<ll>(n,L));
        for(int s=0;s<n;s++){
            vector<ll> d(n,L); d[s]=0;
            priority_queue< pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>> > pq;
            pq.push(make_pair(0,s));
            while(!pq.empty()){
                pair<ll,int> top = pq.top(); pq.pop();
                ll du = top.first;
                int u = top.second;
                if(du!=d[u]) continue;
                for(size_t k=0;k<graph[u].size();k++){
                    int v = graph[u][k].first;
                    ll w = graph[u][k].second;
                    if(d[v]>du+w){ d[v]=du+w; pq.push(make_pair(d[v],v)); }
                }
            }
            dist[s] = d;
        }
        ll sum=0;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) sum+=dist[i][j];
        return sum;
    };

    ll c_orig = all_pairs(adj);

    ll max_c = c_orig;
    for(int i=0;i<m;i++){
        vector<vector<pair<int,ll>>> tmp_adj = adj;
        int u = edges[i].u, v = edges[i].v; ll w = edges[i].w;
        for(size_t k=0;k<tmp_adj[u].size();k++){
            if(tmp_adj[u][k].first==v && tmp_adj[u][k].second==w){
                tmp_adj[u].erase(tmp_adj[u].begin()+k); break;
            }
        }
        for(size_t k=0;k<tmp_adj[v].size();k++){
            if(tmp_adj[v][k].first==u && tmp_adj[v][k].second==w){
                tmp_adj[v].erase(tmp_adj[v].begin()+k); break;
            }
        }
        ll c_new = all_pairs(tmp_adj);
        if(c_new>max_c) max_c=c_new;
    }

    cout << c_orig << " " << max_c << "\n";
}