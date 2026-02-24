#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<int,2>;

constexpr int mod=998244353;

vector<int>g[100005];
int deg[100005];
ll x[100005];
int vis[100005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;++i)cin>>x[i];
	vector<ar>edg(m);
	for(int i=0,u,v;i<m;++i){
		cin>>u>>v;
		edg[i]={u,v};
		++deg[u];
		++deg[v];
	}

	for(int i=0,u,v;i<m;++i){
		u=edg[i][0],v=edg[i][1];
		if(deg[u]<deg[v] or (deg[u]==deg[v] and u<v))
			g[u].push_back(v);
		else
			g[v].push_back(u);
	}

	ll tot=0;
	memset(vis,-1,sizeof vis);
	for(int i=0;i<n;++i){
		for(const int&j:g[i])
			vis[j]=i;
		for(const int&j:g[i])
			for(const int&k:g[j])
				if(vis[k]==i){
					tot+=(x[i]*x[j])%mod*x[k]%mod;
					if(tot>=mod)tot-=mod;
				}
	}
	cout<<tot<<'\n';
}
