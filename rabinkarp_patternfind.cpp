#include <bits/stdc++.h>
using namespace std;

vector<int> rk(string const& p, string const& t) {
    const int b = 31, m = 1000000009;
    int s = p.size(), n = t.size();
    vector<long long> pow(max(s, n));
    pow[0] = 1;
    for (int i = 1; i < (int)pow.size(); i++)
        pow[i] = (pow[i-1] * b) % m;

    vector<long long> h(n + 1, 0);
    for (int i = 0; i < n; i++)
        h[i+1] = (h[i] + (t[i]-'a'+1) * pow[i]) % m;

    long long ph = 0;
    for (int i = 0; i < s; i++)
        ph = (ph + (p[i]-'a'+1) * pow[i]) % m;

    vector<int> res;
    for (int i = 0; i + s - 1 < n; i++) {
        long long cur = (h[i+s] + m - h[i]) % m;
        if (cur == ph * pow[i] % m)
            res.push_back(i);
    }
    return res;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        string txt, pat;
        cin >> txt >> pat;
        vector<int> ans = rk(pat, txt);
        if (ans.empty()) cout << "Not Found\n";
        else {
            cout << ans.size() << "\n";
            for (int i = 0; i < ans.size(); i++) {
                if (i > 0) cout << " ";
                cout << ans[i]+1;
            }
            cout << "\n";
        }
        if (tc) cout << "\n";
    }
}
