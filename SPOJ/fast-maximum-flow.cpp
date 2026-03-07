#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
struct Edge{
	int v, u;
	ll cap,flow=0;
	Edge(int v, int u, ll cap):v(v),u(u),cap(cap){}
};
 
struct Dinic{
	const ll flow_inf=1e18;
	vector<Edge>edges;
	vector<vector<int>>g;
	int n,m=0;
	int s,t;
	vector<int>level,ptr;
	queue<int>Q;
 
	Dinic(int n, int s, int t):n(n),s(s),t(t){
		g.resize(n);
		level.resize(n);
		ptr.resize(n);
	}
 
	void add(int v, int u, ll cap){
		edges.emplace_back(v,u,cap);
		edges.emplace_back(u,v,0);
		edges.emplace_back(u,v,cap);
		edges.emplace_back(v,u,0);
		g[v].push_back(m);
		g[u].push_back(m+1);
		g[u].push_back(m+2);
		g[v].push_back(m+3);
		m+=4;
	}
 
	bool bfs(){
		while(!Q.empty()){
			int v=Q.front();
			Q.pop();
			for(const int&id:g[v]){
				if(edges[id].cap-edges[id].flow<1)
					continue;
				if(level[edges[id].u]!=-1)
					continue;
				level[edges[id].u]=level[v]+1;
				Q.push(edges[id].u);
			}
		}
		return level[t]!=-1;
	}
 
	ll dfs(int v, ll pushed){
		if(pushed==0)
			return 0;
		if(v==t)
			return pushed;
		for(int&cid=ptr[v];cid<g[v].size();++cid){
			int id=g[v][cid];
			int u=edges[id].u;
			if(level[v]+1!=level[u] or edges[id].cap-edges[id].flow<1)
				continue;
			ll tr=dfs(u,min(pushed,edges[id].cap-edges[id].flow));
			if(tr==0)
				continue;
			edges[id].flow+=tr;
			edges[id^1].flow-=tr;
			return tr;
		}
		return 0;
	}
 
	ll flow(){
		ll f=0;
		while(1){
			fill(level.begin(),level.end(),-1);
			level[s]=0;
			Q.push(s);
			if(!bfs())
				break;
			fill(ptr.begin(),ptr.end(),0);
			while(ll pushed=dfs(s,flow_inf))f+=pushed;
		}
		return f;
	}
};
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	Dinic g(n+1,1,n);
	while(m--){
		ll v,u,cap;
		cin>>v>>u>>cap;
		g.add(v,u,cap);
	}
	cout<<g.flow();
}
