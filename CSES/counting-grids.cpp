#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=1e9+7;
 
ll exp(ll a, ll w){
	ll res=1;
	while(w){
		if(w&1) res=res*a%mod;
		a=a*a%mod;
		w>>=1;
	}
	return res;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	ll n;
	cin>>n;
 
	ll n0=n*n;
	ll n90=1;
	ll n180=1;
 
	if(n>1 and n&1){
		n90=(n+3)*(n-1)/4-(n-1)/2+1;
		n180=(n+3)*(n-1)/2-(n-1)+1;
	}
	else if(!(n&1)){
		n90=n*n/4;
		n180=n*n/2;
	}
 
	ll res=0;
	res=exp(2,n0);
	res+=exp(2,n90);
	res%=mod;
	res+=exp(2,n180);
	res%=mod;
	res+=exp(2,n90);
	res%=mod;
	res*=exp(4,mod-2);
	res%=mod;
	cout<<res;
}
