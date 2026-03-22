#include<bits/stdc++.h>
using namespace std;
using ll=long long;

void solve(){
	int n;
	cin>>n;
	vector<int>a(n),ans(n+1);
	for(int&i:a)cin>>i;
	vector<map<int,int>>dp(n);
	for(int i=0;i<n;++i)
		dp[i][a[i]]=1;
	for(int i=1;i<n;++i){
		for(const auto&[gcd,sz]:dp[i-1]){
			int new_gcd=__gcd(gcd,a[i]);
			dp[i][new_gcd]=max(dp[i][new_gcd],sz+1);
		}
	}
	for(int i=0;i<n;++i)
		for(const auto&[gcd,sz]:dp[i])
			ans[sz]=max(ans[sz],gcd);
	for(int i=1;i<=n;++i)
		cout<<ans[i]<<' ';
	cout<<'\n';
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t=1;
	cin>>t;
	while(t--)
		solve();
}

