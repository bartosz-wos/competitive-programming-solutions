#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<int,2>;
 
int n,m,q;
vector<int>dsu(200001,-1);
vector<ar>g[200001];
int depth[200001];
int ptr[200001][20];
int dp[200001][20];
 
int find(int x){
    if(dsu[x]<0)
        return x;
    return dsu[x]=find(dsu[x]);
}
 
bool Union(int a, int b){
    a=find(a);
    b=find(b);
    if(a==b)
        return 0;
    if(dsu[a]>dsu[b])
        swap(a,b);
    dsu[a]+=dsu[b];
    dsu[b]=a;
    return 1;
}
 
void dfs(int v, int e){
    for(const auto&[i,w]:g[v])
        if(i!=e){
            depth[i]=depth[v]+1;
            ptr[i][0]=v;
            dp[i][0]=w;
            dfs(i,v);
        }
}
 
bool same(int a, int b){
    return find(a)==find(b);
}
 
int jump(int v, int k){
    int j=0;
    while(k){
        if(k&1)
            v=ptr[v][j];
        k>>=1;
        ++j;
    }
    return v;
}
 
int mx(int v, int k){
    int ret=0;
    int j=0;
    while(k){
        if(k&1){
            ret=max(ret,dp[v][j]);
            v=ptr[v][j];
        }
        k>>=1;
        ++j;
    }
    return ret;
}
 
int lca(int a, int b){
    if(depth[a]<depth[b])
        swap(a,b);
    a=jump(a,depth[a]-depth[b]);
    if(a==b)
        return a;
    for(int i=19;i>=0;--i)
        if(ptr[a][i]!=ptr[b][i])
            a=ptr[a][i],b=ptr[b][i];
    return ptr[a][0];
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m>>q;
    for(int i=1,a,b;i<=m;++i){
        cin>>a>>b;
        if(Union(a,b)){
            g[a].push_back({b,i});
            g[b].push_back({a,i});
        }
    }
 
    for(int i=1;i<=n;++i)
        if(!depth[i])
            dfs(i,0);
    for(int i=1;i<20;++i)
        for(int j=1;j<=n;++j)
            ptr[j][i]=ptr[ptr[j][i-1]][i-1];
    for(int i=1;i<20;++i)
        for(int j=1;j<=n;++j)
            dp[j][i]=max(dp[j][i-1],dp[ptr[j][i-1]][i-1]);
    while(q--){
        int a,b;
        cin>>a>>b;
        if(!same(a,b)){
            cout<<-1<<'\n';
            continue;
        }
        int x=lca(a,b);
        int q=mx(a,depth[a]-depth[x]);
        int y=mx(b,depth[b]-depth[x]);
        cout<<max(q,y)<<'\n';
    }
}
