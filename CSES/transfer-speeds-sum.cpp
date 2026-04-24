#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
struct DSU{
	vector<int> p;
	vector<ll> sz;
	DSU(int n=0){p.resize(n+1);sz.resize(n+1);for(int i=1;i<=n;i++){p[i]=i;sz[i]=1;}}
	int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
	ll unite(int a,int b){
		a=find(a);b=find(b);
		if(a==b) return 0;
		if(sz[a]<sz[b]) swap(a,b);
		ll prod=sz[a]*sz[b];
		p[b]=a;
		sz[a]+=sz[b];
		return prod;
	}
};
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n; if(!(cin>>n)) return 0;
	struct Edge{int u,v;int w;};
	vector<Edge> edges;
	edges.reserve(n-1);
	for(int i=0;i<n-1;i++){int a,b,x;cin>>a>>b>>x;edges.push_back({a,b,x});}
	sort(edges.begin(),edges.end(),[](const Edge&A,const Edge&B){return A.w>B.w;});
	DSU dsu(n);
	long long ans=0;
	for(auto &e:edges){
		ll pairs=dsu.unite(e.u,e.v);
		ans+=pairs*(ll)e.w;
	}
	cout<<ans<<"\n";
	return 0;
}
