#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, rebra;
    char kakva='\0';
    cin>>n>>rebra;
    cout<<"d ili u matrica: ";
    cin>>kakva;
    vector<vector<int>> adjlist(n);
    int matrica[n][n]={};
    for(int i=0; i<rebra; i++)
    {
        int from=0, to=0;
        cin>>from>>to;
        adjlist[from].push_back(to);
        matrica[from][to]=1;
        if(kakva=='u')
        {
            adjlist[to].push_back(from);
            matrica[to][from]=1;
        }
    }
    cout<<"Lista:";
    cout<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<i<<": ";
        for(int j=0; j<adjlist[i].size(); j++)
        {
            cout<<adjlist[i][j]<<" ";
            
        }
        cout<<endl;
        
    }
    cout<<"Matrica: "<<endl;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<matrica[i][j]<<" ";
        }
        cout<<endl;
    }
    

    return 0;
}
