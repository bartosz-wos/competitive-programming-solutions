#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
constexpr int MAXN=5e3+5;
constexpr int mod=1e9+7;
 
int N;
ll pown[MAXN];
ll fac[MAXN];
ll inv[MAXN];
ll S[MAXN][MAXN];
 
ll inverse(ll a){
	ll ret=1;
	ll w=mod-2;
	while(w){
		if(w&1)
			ret=ret*a%mod;
		a=a*a%mod;
		w>>=1;
	}
	return ret;
}
 
void init_pow(){
	pown[0]=1;
	for(int i=1;i<MAXN;++i)
		pown[i]=pown[i-1]*N%mod;
}
 
void init_C(){
	fac[0]=inv[0]=1;
	for(int i=1;i<MAXN;++i)
		fac[i]=fac[i-1]*(ll)i%mod;
	inv[MAXN-1]=inverse(fac[MAXN-1]);
	for(int i=MAXN-2;i>0;--i)
		inv[i]=inv[i+1]*(ll)(i+1)%mod;
}
 
void init_stirling(){
	S[1][1]=1;
	for(int n=2;n<MAXN;++n)
		for(int k=1;k<=n;++k)
			S[n][k]=(S[n-1][k-1]-(n-1)*S[n-1][k])%mod;
}
 
ll choose(int n, int k){
	if(k<0 or k>n)return 0;
	return fac[n]*inv[k]%mod*inv[n-k]%mod;
}
 
ll stirling1(int n, int k){
	return abs(S[n][k]);
}
 
ll solve(int n, int k){
	ll sum=0;
	for(int j=0;j<n;++j){
		ll a=choose(n-1,j);
		ll b=pown[n-1-j];
		ll c=stirling1(j+1,k);
		sum+=a*b%mod*c%mod;
		sum%=mod;
	}
	return sum;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>N;
	init_pow();
	init_C();
	init_stirling();
	for(int k=1;k<=N;++k)
		cout<<solve(N,k)<<'\n';
}
