#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<pair<int,int>>adj[200005];
vector<int>info[200005];
int sz[200005];
int p[200005];
int fp(int a){return p[a]==a?a:p[a]=fp(p[a]);}
int un(int a,int b,int k){
    a=fp(a),b=fp(b);
    if(info[a].size()>info[b].size())swap(a,b);
    if(sz[a]<k)info[a].clear();
    if(sz[b]<k)info[b].clear();
    for(auto x:info[a])info[b].push_back(x);
    sz[b]+=sz[a];
    return p[a]=b;
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>sz[i];
    vector<pair<int,pair<int,int>>>edge;
    for(int i=1;i<=m;i++){
        int a,b;cin>>a>>b;
        edge.push_back({max(sz[a],sz[b]),{a,b}});
    }
    sort(edge.begin(),edge.end());
    for(int i=1;i<=n;i++)p[i]=i,info[i].push_back(i);
    int rt=1;
    for(auto x:edge){
        int val=x.first;
        int u=x.second.first;
        int v=x.second.second;
        if(fp(u)==fp(v))continue;
        rt=un(u,v,val);
    }
    vector<int>ans(n,0);
    for(auto x:info[rt])ans[x-1]=1;
    for(auto x:ans)cout<<x;
}
