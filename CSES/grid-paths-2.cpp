#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<int,2>;
constexpr int mod=1e9+7;
int n,k;
vector<ar>t;
ll F[2000001];
ll inv[2000001];
ll dp[1001];
 
ll exp(ll a, ll w){
	ll res=1;
	a%=mod;
	while(w){
		if(w&1)
			res=res*a%mod;
		a=a*a%mod;
		w>>=1;
	}
	return res;
}
 
ll f(ll n, ll k){
	if(k>n)
		return 0;
	return F[n]*inv[k]%mod*inv[n-k]%mod;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k;
	t.resize(k+1);
	F[0]=inv[0]=1;
	for(ll i=1;i<=2e6;++i){
		F[i]=F[i-1]*i%mod;
		inv[i]=exp(F[i],mod-2);
	}
	for(ll i=0,y,x;i<k;++i){
		cin>>y>>x;
		t[i]={y-1,x-1};
	}
	t[k]={n-1,n-1};
	sort(t.begin(),t.end());
	for(ll i=0;i<=k;++i){
		dp[i]=f(t[i][0]+t[i][1],t[i][0]);
		for(ll j=0;j<i;++j){
			if(t[j][1]>t[i][1])
				continue;
			dp[i]=(dp[i]-(dp[j]*f(t[i][0]+t[i][1]-t[j][0]-t[j][1],t[i][0]-t[j][0]))%mod+mod)%mod;
		}
	}
	cout<<dp[k];
}
