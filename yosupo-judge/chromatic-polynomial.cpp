#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int g[20];
bool ind[1<<20];
ll dp[1<<20];



int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	while(m--){
		int a,b;
		cin>>a>>b;
		g[a]|=(1<<b);
		g[b]|=(1<<a);
	}
	ind[0]=1;
	for(int msk=1;msk<1<<n;++msk){
		int v=__builtin_ctz(msk);
		if(g[v]&msk)ind[msk]=0;
		else ind[msk]=ind[msk^(1<<v)];
	}
	for(int msk=0;msk<1<<n;++msk)
		dp[msk]=ind[msk];
	for(int i=0;i<n;++i)
		for(int msk=0;msk<1<<n;++msk)
			if(msk&(1<<i))dp[msk]+=dp[msk^(1<<i)];
	for(int k=1;k<=n;++k){
		ll s=0;
		for(int msk=0;msk<1<<n;++msk){
			ll p=1;
			for(int i=0;i<k;++i)p*=dp[msk];
			if((n-__builtin_popcount(msk))&1)s-=p;
			else s+=p;
		}
		if(s){
			cout<<k<<'\n';
			break;
		}
	}
}
