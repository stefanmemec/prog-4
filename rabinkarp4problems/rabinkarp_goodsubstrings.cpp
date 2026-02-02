#include <bits/stdc++.h>
using namespace std;

long long hash_str(string const& t, vector<long long>& pow, long long m) {
    long long h = 0;
    for (int i = 0; i < t.size(); i++)
        h = (h + (t[i]-'a'+1) * pow[i]) % m;
    return h;
}

int main() {
    string s;
    cin >> s;
    string good;
    cin >> good;
    int k;
    cin >> k;

    int n = s.size();
    vector<bool> ok(26, false);
    for (int i = 0; i < 26; i++)
        if (good[i] == '1') ok[i] = true;

    const long long m = 1000000009;
    const int b = 31;
    vector<long long> pow(n);
    pow[0] = 1;
    for (int i = 1; i < n; i++)
        pow[i] = (pow[i-1] * b) % m;

    set<long long> ans;

    for (int i = 0; i < n; i++) {
        int bad = 0;
        string t = "";
        for (int j = i; j < n; j++) {
            t += s[j];
            if (!ok[s[j]-'a']) bad++;
            if (bad > k) break;
            ans.insert(hash_str(t, pow, m));
        }
    }

    cout << ans.size() << "\n";
}
