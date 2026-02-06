#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int N=20;
bool g[N+5][N+5];
ll dp[(1<<N)+5][N+5];

int f(int x){
    int ret=0;
    while(x){
        if(x%3==1)++ret;
        x/=3;
    }
    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<int>a(n),b(n);
    for(int i=0;i<n;++i){
        cin>>a[i];
        b[i]=f(a[i]);
    }
    for(int i=0;i<n;++i)
        for(int j=0;j<i;++j)
            if(__builtin_popcount(a[i])==__builtin_popcount(a[j]) or b[i]==b[j])g[i][j]=g[j][i]=1;
    for(int i=0;i<n;++i)
        dp[1<<i][i]=1;
    for(int mask=0;mask<(1<<n);++mask)
        for(int last=0;last<n;++last)
            if(mask>>last&1)
                for(int nxt=0;nxt<n;++nxt){
                    if(mask>>nxt&1)continue;
                    if(!g[last][nxt])continue;
                    dp[mask|(1<<nxt)][nxt]+=dp[mask][last];
                }
    ll ret=0;
    for(int i=0;i<n;++i)
        ret+=dp[(1<<n)-1][i];
    cout<<ret<<'\n';
}
