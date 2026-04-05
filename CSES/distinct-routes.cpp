#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m;
ll g[501][501];
vector<pair<int,int>>g2[501];
ll res;
bool vis[1000];
int par[501];
vector<int>path;
 
bool bfs(){
	fill(vis+1,vis+n+1,0);
	queue<int>Q;
	Q.push(1);
	vis[1]=1;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		for(int i=1;i<=n;++i)
			if(g[u][i] and !vis[i])
				vis[i]=1,par[i]=u,Q.push(i);
	}
	return vis[n];
}
 
void dfs(int v=1){
	path.push_back(v);
	if(v==n)
		return;
	for(const auto&[i,id]:g2[v])
		if(!g[v][i] and !vis[id]){
			vis[id]=1;
			dfs(i);
			return;
		}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=0,a,b;i<m;++i){
		cin>>a>>b;
		++g[a][b];
		g2[a].push_back({b,i});
	}
	int u,v;
	while(bfs()){
		ll flow=1e18;
		for(v=n;v^1;v=par[v]){
			u=par[v];
			flow=min(flow,g[u][v]);
		}
		res+=flow;
		for(v=n;v^1;v=par[v]){
			u=par[v];
			g[u][v]-=flow;
			g[v][u]+=flow;
		}
	}
	fill(vis+1,vis+n+1,0);
	cout<<res<<'\n';
	while(res--){
		path.clear();
		dfs();
		cout<<path.size()<<'\n';
		for(const int&i:path)
			cout<<i<<' ';
		cout<<'\n';
	}
}

