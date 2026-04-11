#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=1e9+7;
 
string s;
int n,m,k;
ll f[1000001];
ll inv[1000001];
 
ll exp(ll a, ll w){
	ll res=1;
	while(w){
		if(w&1) res=res*a%mod;
		a=a*a%mod;
		w>>=1;
	}
	return res;
}
 
ll nCr(int x, int y){
	return (f[x]*inv[y]%mod*inv[x-y]%mod);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	f[0]=inv[0]=1;
	for(int i=1;i<=1e6;++i){
		f[i]=f[i-1]*i%mod;
		inv[i]=exp(f[i],mod-2);
	}
	cin>>m;
	cin>>s;
	n=s.size();
	int op=0,cl=0;
	for(int i=0;i<n;++i){
		if(s[i]=='(')
			++op;
		else
			++cl;
		if(cl>op){
			cout<<0;
			exit(0);
		}
	}
	if(m&1 or op>m/2){
		cout<<0;
		exit(0);
	}
	ll t=nCr(m-op-cl,m/2-op);
	ll t2=nCr(m-op-cl,m/2-op-1);
	cout<<(t-t2+mod)%mod;
}
