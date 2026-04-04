#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,m,cnt;
bool vis[100001];
vector<int>g[100001],r[100001];
vector<int>kos;
int comp[100001];
 
void dfs1(int v){
    vis[v]=1;
    for(const int&i:g[v])
        if(!vis[i])
            dfs1(i);
    kos.push_back(v);
}
 
void dfs2(int v, const int&e){
    comp[v]=e;
    for(const int&i:r[v])
        if(!comp[i])
            dfs2(i,e);
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    while(m--){
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
        r[b].push_back(a);
    }
    for(int i=1;i<=n;++i)
        if(!vis[i])
            dfs1(i);
    reverse(kos.begin(),kos.end());
    for(const int&i:kos)
        if(!comp[i])
            dfs2(i,++cnt);
    cout<<cnt<<'\n';
    for(int i=1;i<=n;++i)
        cout<<comp[i]<<' ';
}
