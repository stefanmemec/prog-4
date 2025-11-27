#include <bits/stdc++.h>
using namespace std;

string lds(string s){
    int n = s.size();
    long long mod = 1000000007, b = 256;

    string res = "";
    int l = 1, r = n;

    while(l <= r){
        int len = (l+r)/2;
        unordered_set<long long> hs;
        long long h = 0, power = 1;

        for(int i=0;i<len;i++){
            h = (h*b + s[i]) % mod;
            if(i>0) power = (power*b)%mod;
        }
        hs.insert(h);

        string found = "";
        for(int i=len;i<n;i++){
            h = ((h - s[i-len]*power%mod + mod)*b + s[i]) % mod;
            if(hs.count(h)) {
                found = s.substr(i-len+1,len);
                break;
            }
            hs.insert(h);
        }

        if(found!=""){
            res = found;
            l = len+1;
        } else {
            r = len-1;
        }
    }

    return res;
}

int main(){
    string s;
    cin >> s;
    cout << lds(s) << "\n";
}
