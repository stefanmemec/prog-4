#include <bits/stdc++.h>
using namespace std;

long long INF = 1e15;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int mesta, pateki;
    long long L;

    cin >> mesta >> pateki >> L;

    vector<tuple<int, int, long long>> lista;
    vector<vector<long long>> mat(mesta + 1, vector<long long>(mesta + 1, INF));
    for (int i = 1; i <= mesta; i++) mat[i][i] = 0;

    for (int i = 0; i < pateki; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        lista.push_back(make_tuple(a, b, c));
        mat[a][b] = min(mat[a][b], c);
        mat[b][a] = min(mat[b][a], c);
    }

    
        for (int k = 1; k <= mesta; k++)
            for (int i = 1; i <= mesta; i++)
                for (int j = 1; j <= mesta; j++)
                    if (mat[i][k] + mat[k][j] < mat[i][j])
                        mat[i][j] = mat[i][k] + mat[k][j];

       
        auto vkupno = [&](vector<vector<long long>> &d) {
            long long zbir = 0;
            for (int i = 1; i <= mesta; i++) {
                for (int j = 1; j <= mesta; j++) {
                    if (d[i][j] >= INF / 2) zbir += L;
                    else zbir += d[i][j];
                }
            }
            return zbir;
        };

        long long osnovno = vkupno(mat);
        long long maxx = osnovno;

    
        for (auto edge : lista) {
            int a, b;
            long long c;
            tie(a, b, c) = edge;

            vector<vector<long long>> d(mesta + 1, vector<long long>(mesta + 1, INF));
            for (int i = 1; i <= mesta; i++) d[i][i] = 0;

            bool skok = false;
            for (auto edge2 : lista) {
                int x, y;
                long long z;
                tie(x, y, z) = edge2;

              
                if (!skok && ((x == a && y == b && z == c) || (x == b && y == a && z == c))) {
                    skok = true;
                    continue;
                }

                d[x][y] = min(d[x][y], z);
                d[y][x] = min(d[y][x], z);
            }

         
            for (int k = 1; k <= mesta; k++)
                for (int i = 1; i <= mesta; i++)
                    for (int j = 1; j <= mesta; j++)
                        if (d[i][k] + d[k][j] < d[i][j])
                            d[i][j] = d[i][k] + d[k][j];

            long long s = vkupno(d);
            if (s > maxx) maxx = s;
        }

        cout << osnovno << " " << maxx << "\n";
    }

