#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    long long b = 31, m = 1000000009;

    vector<long long> pow(n+1,1);
    for(int i=1;i<=n;i++) pow[i]=(pow[i-1]*b)%m;

    vector<long long> h(n+1,0);
    for(int i=0;i<n;i++) h[i+1]=(h[i]+(s[i]-'a'+1)*pow[i])%m;

    string t = s;
    reverse(t.begin(),t.end());
    vector<long long> hr(n+1,0);
    for(int i=0;i<n;i++) hr[i+1]=(hr[i]+(t[i]-'a'+1)*pow[i])%m;

    vector<vector<int>> k_pal(n,vector<int>(n,0));
    vector<int> ans(n,0);

    for(int len=1;len<=n;len++){
        for(int i=0;i+len<=n;i++){
            int j=i+len-1;
            long long x=(h[j+1]-h[i]+m)%m;
            x=(x*pow[n-i-1])%m;
            long long y=(hr[n-j-1+len]-hr[n-j-1]+m)%m;
            y=(y*pow[n-(n-j-1)-1])%m;
            if(x==y) k_pal[i][j]=1;
        }
    }

    for(int len=1;len<=n;len++){
        for(int i=0;i+len<=n;i++){
            int j=i+len-1;
            if(!k_pal[i][j]) continue;
            int k=1,l=i,r=j;
            while(l<r){
                int mid=(l+r)/2;
                if(k_pal[l][mid] && k_pal[mid+1][r]) k++;
                else break;
                r=mid;
            }
            ans[k-1]++;
        }
    }

    for(int i=0;i<n;i++){
        cout << ans[i];
        if(i<n-1) cout << " ";
        else cout << "\n";
    }
}
