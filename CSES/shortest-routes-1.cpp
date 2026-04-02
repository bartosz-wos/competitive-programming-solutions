#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<ll,ll>;
 
vector<pi>g[100005];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	while(m--){
		ll a,b,c;
		cin>>a>>b>>c;
		g[a].push_back({b,c});
	}
	vector<ll>dist(n+1,1e16);
	vector<bool>vis(n+1,0);
	vis[1]=0;
	dist[1]=0;
	priority_queue<pi,vector<pi>,greater<pi>>pq;
	pq.push({0,1});
	while(!pq.empty()){
		int v=pq.top().second;
		ll d=pq.top().first;
		pq.pop();
		if(vis[v])continue;
		vis[v]=1;
		for(const auto&[u,c]:g[v])
			if(dist[u]>dist[v]+c){
				dist[u]=dist[v]+c;
				pq.push({dist[u],u});
			}
	}
	for(int i=1;i<=n;++i)
		cout<<dist[i]<<' ';
}
