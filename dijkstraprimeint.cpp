#include <bits/stdc++.h>
using namespace std;

void dijkstraPrimes(int maxNum) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
   
    cout << 2 << " ";
    q.push({4, 2});

    for (int x = 3; x <= maxNum; x++) {
        if (x < q.top().first) {
            cout << x << " ";
            q.push({x * x, x});
        } else {
            while (x == q.top().first) {
                auto p = q.top();
                q.pop();
                q.push({p.first + p.second, p.second});
            }
        }
    }
    cout << endl;
}

int main() {
    dijkstraPrimes(50);
    return 0;
}
