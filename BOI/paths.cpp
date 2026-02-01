#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=3e5+5;

int a[N];
vector<int>g[N];

ll dp[1<<5][N];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i){
      cin>>a[i];
      --a[i];dp[1<<a[i]][i]=1;
    }
    for(int i=0,a,b;i<m;++i){
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int msk=0;msk<(1<<k);++msk)
        for(int i=1;i<=n;++i){
            if(msk&(1<<a[i]))continue;
            for(const int&j:g[i]){
                if(!(msk&(1<<a[j])))continue;
                dp[msk^(1<<a[i])][i]+=dp[msk][j];
            }
        }
    ll ans=0;
    for(int i=1;i<=n;++i)
        for(int msk=0;msk<(1<<k);++msk)
            if(__builtin_popcount(msk)>=2)
                ans+=dp[msk][i];
    cout<<ans<<'\n';
}
