#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18; 

int main() {
    int V, E; 
    cin >> V >> E;

    vector<vector<long long>> dist(V, vector<long long>(V, INF));

    for (int i = 0; i < V; i++) 
        dist[i][i] = 0;

    
    for (int i = 0; i < E; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = w;
        dist[v][u] = w; 
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cout << "Najkratkata distanca od site parovi: "<<endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << dist[i][j] << " ";
        }
        cout <<endl;
    }

    return 0;
}
