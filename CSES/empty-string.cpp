#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int maxn=501;
constexpr int mod=1e9+7;
 
int n;
string s;
ll f[maxn],inv[maxn],dp[maxn][maxn];
 
ll exp(ll a, ll w){
	ll ret=1;
	while(w){
		if(w&1)
			ret=ret*a%mod;
		a=a*a%mod;
		w>>=1;
	}
	return ret;
}
 
ll choose(int n, int k){
	if(k>n or k<0)return 0;
	return f[n]*inv[k]%mod*inv[n-k]%mod;
}
 
void init(){
	f[0]=inv[0]=1;
	for(int i=1;i<maxn;++i){
		f[i]=(f[i-1]*(ll)i)%mod;
		inv[i]=exp(f[i],mod-2);
	}
	memset(dp,-1,sizeof(dp));
}
 
ll solve(int l, int r){
	if((r-l+1)&1)return 0;
	if(l>r)return 1;
	if(dp[l][r]!=-1)return dp[l][r];
	ll ret=0;
	for(int k=l+1;k<=r;++k)
		if(s[l]==s[k]){
			ll sub=solve(l+1,k-1)*solve(k+1,r)%mod;
			ll comb=sub*choose((r-l+1)/2,(k-l+1)/2)%mod;
			ret=(ret+comb)%mod;
		}
	return dp[l][r]=ret;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	init();
	cin>>s;
	n=s.size();
	cout<<(n&1?0:solve(0,n-1))<<'\n';
}
