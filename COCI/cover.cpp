#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;

#define fi first
#define se second

constexpr int N=5e3+5;

int n;
pi a[N];
ll dp[N];

bool cmp(pi x, pi y){
        if(x.fi^y.fi)return x.fi<y.fi;
        return x.se>y.se;
}

int main(){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin>>n;
        for(int i=1;i<=n;++i){
                cin>>a[i].fi>>a[i].se;
                a[i].fi=abs(a[i].fi);
                a[i].se=abs(a[i].se);
        }
        sort(a+1,a+n+1,cmp);
        dp[0]=0;
        fill(dp+1,dp+n+1,1e18);
        dp[1]=a[1].fi*a[1].se;
        for(int i=2;i<=n;++i){
                ll mx=a[i].se;
                for(int j=i;j;--j){
                        mx=max(mx,a[j].se);
                        dp[i]=min(dp[i],dp[j-1]+mx*a[i].fi);
                }
        }
        cout<<(dp[n]<<2)<<'\n';
}

