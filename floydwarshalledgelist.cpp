#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,int>>> lista(n);


    for (int i = 0; i < m; i++) {
        int a, b, tezina;
        cin >> a >> b >> tezina;
        lista[a].push_back({b, tezina});
        lista[b].push_back({a, tezina});
    }

    vector<vector<int>> dalecina(n, vector<int>(n, INF));

  
    for (int i = 0; i < n; i++) {
        dalecina[i][i] = 0;
        for (auto par : lista[i]) {
            int sosed = par.first, tezina = par.second;
            dalecina[i][sosed] = min(dalecina[i][sosed], tezina);
        }
    }

   
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dalecina[i][k] < INF && dalecina[k][j] < INF)
                    dalecina[i][j] = min(dalecina[i][j], dalecina[i][k] + dalecina[k][j]);

   
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dalecina[i][j] == INF) cout << "INF ";
            else cout << dalecina[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
