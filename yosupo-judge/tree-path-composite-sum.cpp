#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<ll,3>;

constexpr int mod=998244353;

int n;
vector<ar>g[200005];
int a[200005];
ll sz[200005];
ll dp[200005];
ll ans[200005];

void dfs1(int v, int e=-1){
	sz[v]=1;
	dp[v]=a[v];
	for(const auto&[u,b,c]:g[v]){
		if(u==e)continue;
		dfs1(u,v);
		sz[v]+=sz[u];
		dp[v]+=(b*dp[u]%mod+c*sz[u]%mod)%mod;
		if(dp[v]>=mod)dp[v]-=mod;
	}
}

void dfs2(int v, int e=-1, ll val=0){
	ans[v]=dp[v]+val;
	if(ans[v]>=mod)ans[v]-=mod;
	for(const auto&[u,b,c]:g[v]){
		if(u==e)continue;
		ll sum_no_u=b*dp[u]%mod+c*sz[u]%mod;
		if(sum_no_u>=mod)sum_no_u-=mod;
		sum_no_u=ans[v]-sum_no_u;
		if(sum_no_u<0)sum_no_u+=mod;
		ll val2=b*sum_no_u%mod+c*((ll)n-sz[u])%mod;
		if(val2>=mod)val2-=mod;
		dfs2(u,v,val2);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=0;i<n;++i)
		cin>>a[i];
	for(int i=1,a,b;i<n;++i){
		ll c,d;
		cin>>a>>b>>c>>d;
		g[a].push_back({b,c,d});
		g[b].push_back({a,c,d});
	}
	dfs1(0);
	dfs2(0);
	for(int i=0;i<n;++i)
		cout<<ans[i]<<' ';
	cout<<'\n';
}
