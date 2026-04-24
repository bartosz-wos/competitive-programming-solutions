#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,q;
	if(!(cin>>n>>q))return 0;
	vector<int> has(n+1);
	for(int i=1;i<=n;i++)cin>>has[i];
	vector<vector<int>> adj(n+1);
	for(int i=0;i<n-1;i++){
		int a,b;cin>>a>>b;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	const int INF=1e9;
	vector<int> distCoin(n+1,INF);
	queue<int> qu;
	for(int i=1;i<=n;i++)if(has[i]){distCoin[i]=0;qu.push(i);}
	while(!qu.empty()){
		int u=qu.front();qu.pop();
		for(int v:adj[u])if(distCoin[v]==INF){
			distCoin[v]=distCoin[u]+1;
			qu.push(v);
		}
	}
	int LOG=1;
	while((1<<LOG)<=n)LOG++;
	vector<int> parent(n+1,0),depth(n+1,0),sz(n+1,0),heavy(n+1,-1);
	function<void(int,int)> dfs1=[&](int u,int p){
		parent[u]=p;
		sz[u]=1; heavy[u]=-1;
		for(int v:adj[u])if(v!=p){
			depth[v]=depth[u]+1;
			dfs1(v,u);
			if(heavy[u]==-1||sz[v]>sz[heavy[u]]) heavy[u]=v;
			sz[u]+=sz[v];
		}
	};
	depth[1]=0;
	dfs1(1,1);
	vector<int> head(n+1),pos(n+1);
	int cur=0;
	function<void(int,int)> dfs2=[&](int u,int h){
		head[u]=h;
		pos[u]=++cur;
		if(heavy[u]!=-1) dfs2(heavy[u],h);
		for(int v:adj[u])if(v!=parent[u]&&v!=heavy[u]){
			dfs2(v,v);
		}
	};
	dfs2(1,1);
	vector<vector<int>> up(LOG,vector<int>(n+1));
	for(int v=1;v<=n;v++)up[0][v]=parent[v];
	for(int k=1;k<LOG;k++)for(int v=1;v<=n;v++)up[k][v]=up[k-1][ up[k-1][v] ];
	auto lca=[&](int a,int b){
		if(depth[a]<depth[b])swap(a,b);
		int dif=depth[a]-depth[b];
		for(int k=0;k<LOG;k++) if(dif&(1<<k)) a=up[k][a];
		if(a==b) return a;
		for(int k=LOG-1;k>=0;k--) if(up[k][a]!=up[k][b]){ a=up[k][a]; b=up[k][b]; }
		return parent[a];
	};
	auto distNode=[&](int a,int b)->int{
		int c=lca(a,b);
		return depth[a]+depth[b]-2*depth[c];
	};
	vector<int> base(n+1);
	for(int v=1;v<=n;v++) base[pos[v]]=distCoin[v];
	int SZ=1;
	while(SZ<n)SZ<<=1;
	vector<int> seg(2*SZ,INF);
	for(int i=1;i<=n;i++) seg[SZ+pos[i]-1]=base[pos[i]];
	for(int i=SZ-1;i>0;i--) seg[i]=min(seg[2*i],seg[2*i+1]);
	auto seg_query=[&](int l,int r){
		l+=SZ-1; r+=SZ-1;
		int res=INF;
		while(l<=r){
			if(l&1) res=min(res,seg[l++]);
			if(!(r&1)) res=min(res,seg[r--]);
			l>>=1; r>>=1;
		}
		return res;
	};
	auto path_min=[&](int a,int b){
		int res=INF;
		while(head[a]!=head[b]){
			if(depth[head[a]]<depth[head[b]]) swap(a,b);
			int h=head[a];
			res=min(res, seg_query(pos[h], pos[a]));
			a=parent[h];
		}
		if(depth[a]>depth[b]) swap(a,b);
		res=min(res, seg_query(pos[a], pos[b]));
		return res;
	};
	for(int i=0;i<q;i++){
		int a,b;cin>>a>>b;
		int d=distNode(a,b);
		int mn=path_min(a,b);
		ll ans=(ll)d + 2LL*(ll)mn;
		cout<<ans<<"\n";
	}
	return 0;
}
