#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=1e9+7;
int ind[26];
ll dp[500001];
string s;
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>s;
	int n=s.size();
	fill(ind,ind+26,-1);
	dp[0]=1;
	for(int i=1;i<=n;++i){
		dp[i]=2*dp[i-1];
		if(ind[s[i-1]-97]>=0)
			dp[i]-=dp[ind[s[i-1]-97]];
		dp[i]=(dp[i]+mod)%mod;
		ind[s[i-1]-'a']=i-1;
	}
	cout<<(dp[n]-1+mod)%mod;
}
