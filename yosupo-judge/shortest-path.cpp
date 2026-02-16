#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<ll,2>;

int n,m,s,t;
vector<pi>g[500005];
int par[500005];
ll dist[500005];
bool vis[500005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m>>s>>t;
	while(m--){
		ll a,b,c;
		cin>>a>>b>>c;
		g[a].push_back({b,c});
	}
	memset(dist,-1,sizeof dist);
	priority_queue<pi,vector<pi>,greater<pi>>q;
	q.push({0,s});
	dist[s]=0;
	while(!q.empty()){
		ll d=q.top()[0];
		int u=q.top()[1];
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(const auto&[v,c]:g[u])
			if(!~dist[v] or (~dist[v] and dist[v]>dist[u]+c)){
				par[v]=u;
				dist[v]=dist[u]+c;
				q.push({dist[v],v});
			}
	}
	if(!~dist[t]){
		cout<<-1<<'\n';
		return 0;
	}
	cout<<dist[t]<<' ';
	vector<pi>res;
	while(t!=s){
		res.push_back({par[t],t});
		t=par[t];
	}
	reverse(res.begin(),res.end());
	cout<<res.size()<<'\n';
	for(const auto&[a,b]:res)
		cout<<a<<' '<<b<<'\n';
}
