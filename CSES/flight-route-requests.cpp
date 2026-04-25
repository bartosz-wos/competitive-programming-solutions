#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int MAXN=1e5+5;
 
int N,M,ds[MAXN],vis[MAXN];
vector<int>G[MAXN],CC[MAXN];
 
void init(){
    iota(ds,ds+MAXN,0);
}
 
int find(int v){
    if(ds[v]==v)return v;
    return ds[v]=find(ds[v]);
}
 
bool merge(int a, int b){
    a=find(a);
    b=find(b);
    if(a==b)return 0;
    ds[b]=a;
    return 1;
}
 
bool dfs(int u){
    vis[u]=-1;
    bool ok=0;
    for(const int&v:G[u]){
        if(vis[v]==-1)return 1;
        else if(vis[v]==0)ok|=dfs(v);
    }
    vis[u]=1;
    return ok;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>N>>M;
    init();
    while(M--){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        merge(a,b);
    }
    int K=0;
    unordered_map<int,int>mp;
    for(int i=1;i<=N;++i){
        int rep=find(i);
        if(!mp.count(rep))
            mp[rep]=++K;
        CC[mp[rep]].push_back(i);
    }
    int res=0;
    for(int k=1;k<=K;++k){
        int sz=CC[k].size();
        bool ok=0;
        for(const int&u:CC[k])
            if(!ok and !vis[u])
                ok|=dfs(u);
        res+=ok?sz:sz-1;
    }
    cout<<res<<'\n';
}
