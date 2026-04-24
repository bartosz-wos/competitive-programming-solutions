#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m; if(!(cin>>n>>m))return 0;
	struct Edge{int u,v;int w;int id;};
	vector<Edge> edges; edges.reserve(m);
	for(int i=0;i<m;i++){int a,b,w;cin>>a>>b>>w;edges.push_back({a,b,w,i});}
	vector<Edge> sorted=edges;
	sort(sorted.begin(),sorted.end(),[](const Edge&A,const Edge&B){return A.w<B.w;});
	vector<int> p(n+1),sz(n+1);
	for(int i=1;i<=n;i++){p[i]=i;sz[i]=1;}
	function<int(int)> findp=[&](int x){return p[x]==x?x:p[x]=findp(p[x]);};
	auto unite=[&](int a,int b)->bool{
		a=findp(a);b=findp(b);
		if(a==b) return false;
		if(sz[a]<sz[b]) swap(a,b);
		p[b]=a; sz[a]+=sz[b];
		return true;
	};
	vector<char> inMST(m,0);
	ll mstSum=0;
	int used=0;
	for(auto &e:sorted){
		if(unite(e.u,e.v)){
			inMST[e.id]=1;
			mstSum+=e.w;
			used++;
			if(used==n-1) break;
		}
	}
	vector<vector<pair<int,int>>> adj(n+1);
	for(auto &e:edges) if(inMST[e.id]){
		adj[e.u].pb({e.v,e.w});
		adj[e.v].pb({e.u,e.w});
	}
	int LOG=1;
	while((1<<LOG)<=n)LOG++;
	vector<vector<int>> up(LOG,vector<int>(n+1,0));
	vector<vector<int>> maxw(LOG,vector<int>(n+1,0));
	vector<int> depth(n+1,0);
	// DFS stack
	vector<int> st;
	st.pb(1);
	up[0][1]=1;
	depth[1]=0;
	vector<int> parent(n+1,0), pw(n+1,0);
	parent[1]=1; pw[1]=0;
	while(!st.empty()){
		int u=st.back(); st.pop_back();
		for(auto &pr:adj[u]){
			int v=pr.fi,w=pr.se;
			if(v==parent[u]) continue;
			parent[v]=u; pw[v]=w;
			depth[v]=depth[u]+1;
			up[0][v]=u;
			maxw[0][v]=w;
			st.pb(v);
		}
	}
	up[0][1]=1; maxw[0][1]=0;
	for(int k=1;k<LOG;k++){
		for(int v=1;v<=n;v++){
			up[k][v]=up[k-1][ up[k-1][v] ];
			maxw[k][v]=max(maxw[k-1][v], maxw[k-1][ up[k-1][v] ]);
		}
	}
	auto query_max=[&](int a,int b)->int{
		if(a==b) return 0;
		int res=0;
		if(depth[a]<depth[b]) swap(a,b);
		int dif=depth[a]-depth[b];
		for(int k=0;k<LOG;k++) if(dif&(1<<k)){
			res=max(res,maxw[k][a]);
			a=up[k][a];
		}
		if(a==b) return res;
		for(int k=LOG-1;k>=0;k--){
			if(up[k][a]!=up[k][b]){
				res=max(res,maxw[k][a]);
				res=max(res,maxw[k][b]);
				a=up[k][a];
				b=up[k][b];
			}
		}
		res=max(res,maxw[0][a]);
		res=max(res,maxw[0][b]);
		return res;
	};
	for(auto &e:edges){
		if(inMST[e.id]){
			cout<<mstSum<<"\n";
		}else{
			int mx=query_max(e.u,e.v);
			ll ans=mstSum + (ll)e.w - (ll)mx;
			cout<<ans<<"\n";
		}
	}
	return 0;
}
