#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int mod=998244353;
int x[105];

bitset<105>g[105];
ll ans=0;

void dfs(int v, bitset<105>bs, ll prod){
	ans+=prod;
	if(ans>=mod)ans-=mod;
	bitset<105>nxt=bs&g[v];
	int i=nxt._Find_next(v);
	while(i!=105){
		dfs(i,nxt,prod*x[i]%mod);
		nxt.flip(i);
		i=nxt._Find_next(i);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;++i)cin>>x[i];
	while(m--){
		int a,b;
		cin>>a>>b;
		g[a].set(b);
		g[b].set(a);
	}
	bitset<105>bs;
	for(int i=0,j=0;i<n;++i,j=i){
		bs.reset();
		j=g[i]._Find_next(j);
		while(j!=105){
			bs.set(j);
			j=g[i]._Find_next(j);
		}
		dfs(i,bs,x[i]);
	}
	cout<<ans<<'\n';
}
