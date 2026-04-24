#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,q;
    if(!(cin>>n>>m>>q))return 0;
    vector<vector<int>> adj2(2*n);
    auto id = [&](int v,int parity){ return (v-1)*2 + parity; };
    for(int i=0;i<m;i++){
        int u,v;cin>>u>>v;
        adj2[id(u,0)].push_back(id(v,1));
        adj2[id(v,1)].push_back(id(u,0));
        adj2[id(u,1)].push_back(id(v,0));
        adj2[id(v,0)].push_back(id(u,1));
    }
    vector<vector<int>> dist(n+1, vector<int>(2*n, INF));
    queue<int> qu;
    for(int s=1;s<=n;s++){
        auto &d = dist[s];
        while(!qu.empty()) qu.pop();
        int src = id(s,0);
        d[src]=0;
        qu.push(src);
        while(!qu.empty()){
            int u = qu.front(); qu.pop();
            for(int v: adj2[u]){
                if(d[v]==INF){
                    d[v]=d[u]+1;
                    qu.push(v);
                }
            }
        }
    }
    for(int i=0;i<q;i++){
        int a,b; long long x;
        cin>>a>>b>>x;
        int parity = (int)(x&1LL);
        int target = id(b,parity);
        int best = dist[a][target];
        if(best<=x) cout<<"YES\n"; else cout<<"NO\n";
    }
    return 0;
}
