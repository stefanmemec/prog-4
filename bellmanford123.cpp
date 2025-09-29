#include<bits/stdc++.h>
using namespace std;
struct Edge{
   int u, x, w;
};
void bellmanford(int V, int e,vector<Edge>edges, int src)
{
    vector<long long>dist(V, LLONG_MAX);
    dist[src]=0;
    for(int i=0; i<V-1; i++)
    {
        for(int j=0; j<e; j++)
        {
           int u=edges[j].u;
           int x=edges[j].x;
           int w=edges[j].w;
           if(dist[u]!=LLONG_MAX && dist[u]+w<dist[x])
           {
            dist[x]=dist[u]+w;
           }
        }
    }
    for(int i=0; i<e; i++)
    {
        int u=edges[i].u;
        int x=edges[i].x;
        int w=edges[i].w;
        if(dist[u]!=LLONG_MAX&&dist[u]+w<dist[x])
           {
            return;
           }

    }
    cout<<"Distanca od "<<src<<" do sekoe teme pretstavuva: "<<endl;
    for(int i=1; i<=V; i++)
    {
        cout<<i<<": "<<dist[i]<<endl;
    }

}

int main()
{
    int V, e;
    cin>>V>>e;
    vector<Edge> edges;
    for(int i=0; i<e; i++)
    {
        int u, x, w;
        cin>>u>>x>>w;
        edges.push_back({u,x,w}); 
    }
    int src;
    cin>>src;
    bellmanford(V,e,edges,src);

}