#include <bits/stdc++.h>
using namespace std;
using ll=long long;

void solve(){
    ll n,x;
    cin>>n>>x;
    vector<ll>a(n);
    for(ll&i:a)cin>>i;
    vector<ll>dp[2];
    for(int i=0;i<2;++i)dp[i].resize(n,0);
    for(int i=1;i<n;++i){
        dp[0][i]=dp[0][i-1]+(a[i]^a[i-1]);
        dp[0][i]=max(dp[0][i],dp[1][i-1]+(a[i]^(a[i-1]+x)));
        dp[1][i]=dp[0][i-1]+((a[i]+x)^a[i-1]);
        dp[1][i]=max(dp[1][i],dp[1][i-1]+((a[i]+x)^(a[i-1]+x)));
    }
    if(n==1){
        cout<<0<<'\n';
        return;
    }
    cout<<max(dp[0][n-1],dp[1][n-1])<<'\n';
}

int main() {
	int t;
	cin>>t;
	while(t--)solve();
}

