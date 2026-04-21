#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr ll inf=1LL<<60;
 
int n,m,k,p[501];
ll d[501];
bool in[501];
vector<int>g[501],ret;
bool vis[1001];
 
struct Edge{
	int u,v;
	ll r,c;
}edges[1001],redges[1001];
 
void spfa(){
	memset(in,0,sizeof(in));
	memset(p,0,sizeof(p));
	fill(d+1,d+n+1,inf);
	queue<int>Q;
	Q.push(1);
	in[1]=1;
	d[1]=0;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		in[u]=0;
		for(const int&i:g[u]){
			Edge e=(i<0?redges[-i]:edges[i]);
			if(e.r>0 and d[e.v]>d[u]+e.c){
				d[e.v]=d[u]+e.c;
				p[e.v]=i;
				if(!in[e.v]){
					in[e.v]=1;
					Q.push(e.v);
				}
			}
		}
	}
}
 
ll mcmf(){
	ll flow=0,cost=0;
	while(flow<k){
		spfa();
		if(d[n]==inf)break;
		ll aug=k-flow;
		int u=n;
		while(u!=1){
			Edge e=(p[u]<0?redges[-p[u]]:edges[p[u]]);
			aug=min(aug,e.r);
			u=e.u;
		}
		flow+=aug;
		cost+=aug*d[n];
		u=n;
		while(u!=1){
			if(p[u]<0){
				redges[-p[u]].r-=aug;
				edges[-p[u]].r+=aug;
			}else{
				redges[p[u]].r+=aug;
				edges[p[u]].r-=aug;
			}
			u=(p[u]<0?redges[-p[u]].u:edges[p[u]].u);
		}
	}
	return (flow<k?-1:cost);
}
 
void dfs(int v=1){
	ret.push_back(v);
	if(v==n)return;
	for(const int&i:g[v])
		if(i>0 and edges[i].r==0 and !vis[i]){
			vis[i]=1;
			dfs(edges[i].v);
			return;
		}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m>>k;
	for(int i=1,u,v,r,c;i<=m;++i){
		cin>>u>>v;
		g[u].push_back(i);
		g[v].push_back(-i);
		edges[i]={u,v,1,1};
		redges[i]={v,u,0,-1};
	}
	int mcf=mcmf();
	if(mcf==-1){
		cout<<-1<<'\n';
		exit(0);
	}
	cout<<mcf<<'\n';
	for(int i=0;i<k;++i){
		ret.clear();
		dfs();
		cout<<ret.size()<<'\n';
		for(const int&j:ret)cout<<j<<' ';
		cout<<'\n';
	}
}
