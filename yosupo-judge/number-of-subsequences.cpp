#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;

ll dp[500005];
map<int,int>mp;

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	dp[0]=1;
	int n;
	cin>>n;
	for(int i=1,x;i<=n;++i){
		cin>>x;
		dp[i]+=2*dp[i-1];
		while(dp[i]>=mod)dp[i]-=mod;
		if(mp.count(x)){
			dp[i]-=dp[mp[x]-1];
			if(dp[i]<0)dp[i]+=mod;
		}
		mp[x]=i;
	}
	--dp[n];
	if(dp[n]<0)dp[n]+=mod;
	cout<<dp[n]<<'\n';
}
