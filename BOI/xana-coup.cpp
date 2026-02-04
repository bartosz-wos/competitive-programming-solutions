#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=1e5+5;
constexpr int inf=1e9;

int n;
int dp[N][2][2];

int a[N];
vector<int>g[N];

void dfs(int v, int e){
    for(const int&i:g[v]){
        if(i==e)continue;
        dfs(i,v);
    }
    vector<int>all;
    ll tot=0;
    for(const int&i:g[v]){
        if(i==e)continue;
        tot+=dp[i][a[i]][0];
        all.push_back(dp[i][a[i]][1]-dp[i][a[i]][0]);
    }
    sort(all.begin(),all.end());
    vector<ll>p(all.size()+1);
    for(int i=1;i<=all.size();++i)
        p[i]=p[i-1]+all[i-1];
    vector<ll>mn(2,inf);
    for(int i=0;i<=all.size();++i)
        mn[i&1]=min(mn[i&1],tot+p[i]);
    dp[v][0][0]=mn[0];
    dp[v][1][0]=mn[1];
    all.clear();
    tot=0;
    for(const int&i:g[v]){
        if(i==e)continue;
        tot+=dp[i][a[i]^1][0];
        all.push_back(dp[i][a[i]^1][1]-dp[i][a[i]^1][0]);
    }
    sort(all.begin(),all.end());
    mn[0]=mn[1]=inf;
    for(int i=1;i<=all.size();++i)
        p[i]=p[i-1]+all[i-1];
    for(int i=0;i<=all.size();++i)
        mn[i&1]=min(mn[i&1],tot+p[i]+1);
    dp[v][0][1]=mn[1];
    dp[v][1][1]=mn[0];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n;
    for(int i=1,a,b;i<n;++i){
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i=1;i<=n;++i)
        cin>>a[i];
    dfs(1,-1);
    int ret=min(dp[1][a[1]][0],dp[1][a[1]][1]);
    if(ret==inf)
        cout<<"impossible\n";
    else
        cout<<ret<<'\n';
}
