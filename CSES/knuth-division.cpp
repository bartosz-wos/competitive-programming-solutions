#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n;
int t[5001];
ll pref[5001];
ll dp[5001][5001];
ll opt[5001][5001];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>t[i];
		pref[i]=pref[i-1]+t[i];
		opt[i][i]=i;
	}
 
	auto get=[&](int l, int r){return pref[r]-pref[l-1];};
 
	for(int l=n-1;l>=1;--l)
		for(int r=l+1;r<=n;++r){
			ll res=1e18;
			ll cost=get(l,r);
			for(int k=opt[l][r-1];k<=min((ll)r-1,opt[l+1][r]);++k)
				if(res>=dp[l][k]+dp[k+1][r]){
					opt[l][r]=k;
					res=dp[l][k]+dp[k+1][r];
				}
			dp[l][r]=res+cost;
		}
	cout<<dp[1][n];
}
