#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=1e4+5;
constexpr int inf=1e9;
int n,k,s,sz[N];
vector<pair<int,int>>g[N];
int dp[N][N][2];

int szdfs(int v, int e){
    sz[v]=1;
    for(const auto&[i,w]:g[v])
        if(i!=e)szdfs(i,v),sz[v]+=sz[i];
    return sz[v];
}

void ckmn(int&x, int y){
    x=min(x,y);
}

void dfs(int v, int e){
    int tot=1;
    for(const auto&[u,w]:g[v])
        if(u!=e){
            dfs(u,v);
            tot+=sz[u];
            for(int i=tot;i>=2;--i)
                for(int j=max(0,i+sz[u]-tot);j<=min(i,sz[u]);++j){
                    ckmn(dp[v][i][0],dp[v][i-j][0]+dp[u][j][1]+2*w);
                    ckmn(dp[v][i][0],dp[v][i-j][1]+dp[u][j][0]+w);
                    ckmn(dp[v][i][1],dp[v][i-j][1]+dp[u][j][1]+2*w);
                }
        }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>k>>s;
    for(int i=1,a,b,c;i<n;++i){
        cin>>a>>b>>c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    for(int i=1;i<=n;++i)
        for(int j=2;j<=n;++j)
            dp[i][j][0]=dp[i][j][1]=inf;
    szdfs(s,-1);
    dfs(s,-1);
    cout<<dp[s][k][0]<<'\n';
}
