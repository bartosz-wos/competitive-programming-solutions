#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mod=998244353;

struct dsu{
	vector<int>p;
	vector<ll>d;
	dsu(int n){
		p.resize(n+1,-1);
		d.resize(n+1,0);
	}
	pair<int,ll>fd(int x){
		if(p[x]<0)return {x,0};
		auto [v,d2]=fd(p[x]);
		ll d3=(d2+d[x])%mod;
		p[x]=v;
		d[x]=d3;
		return {v,d[x]};
	}
	bool unite(int a, int b, ll x){
		auto [a2,da]=fd(a);
		auto [b2,db]=fd(b);
		if(a2==b2)return (da-db+mod)%mod==x%mod;
		ll d2=(x-da+db+mod)%mod;
		p[b2]+=p[a2];
		p[a2]=b2;
		d[a2]=d2;
		return 1;
	}
};

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q;
	cin>>n>>q;
	dsu g(n);
	while(q--){
		int t,u,v;
		cin>>t>>u>>v;
		if(!t){
			ll x;
			cin>>x;
			cout<<g.unite(u,v,x)<<'\n';
		}else{
			auto [u2,du]=g.fd(u);
			auto [v2,dv]=g.fd(v);
			cout<<(u2^v2?-1:(du-dv+mod)%mod)<<'\n';
		}
	}
}
