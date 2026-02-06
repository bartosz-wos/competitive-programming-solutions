#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=2e5+5;
constexpr int K=505;

int n,k;
vector<int>g[N];
int a[N],sz[N];
int dp[N][K];

void dfs(int u){
    sz[u]=1;
    for(const int&v:g[u]){
        dfs(v);
        for(int i=sz[u];i>=0;--i)
            for(int j=min(sz[v],k-i);j>=0;--j)
                dp[u][i+j]=max(dp[u][i+j],dp[v][j]+dp[u][i]);
        sz[u]+=sz[v];
        if(sz[u]>=k)sz[u]=k;
    }
    dp[u][1]=max(dp[u][1],a[u]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>k;
    for(int i=0;i<=n;++i)
        for(int j=0;j<=k;++j)dp[i][j]=-1e9;
    int root=0;
    for(int i=1,j;i<=n;++i){
        cin>>j>>a[i];
        if(j)g[j].push_back(i);
        else root=i;
        dp[i][0]=0;
    }
    dfs(root);
    cout<<dp[root][k]<<'\n';
}
