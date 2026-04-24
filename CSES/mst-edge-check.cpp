#include<bits/stdc++.h>
using namespace std;
using ll=long long;
#define fi first
#define se second
#define pb push_back
 
struct DSU{
	vector<int> p,sz;
	DSU(int n=0){p.resize(n+1);sz.resize(n+1);for(int i=1;i<=n;i++){p[i]=i;sz[i]=1;}}
	int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
	bool unite(int a,int b){
		a=find(a);b=find(b);
		if(a==b) return false;
		if(sz[a]<sz[b]) swap(a,b);
		p[b]=a; sz[a]+=sz[b];
		return true;
	}
};
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n,m; if(!(cin>>n>>m))return 0;
	struct E{int u,v;int w;int id;};
	vector<E> edges; edges.reserve(m);
	for(int i=0;i<m;i++){int a,b,w;cin>>a>>b>>w;edges.push_back({a,b,w,i});}
	sort(edges.begin(),edges.end(),[](const E&A,const E&B){return A.w<B.w;});
	DSU dsu(n);
	vector<string> ans(m,"NO");
	for(int i=0;i<m;){
		int j=i;
		while(j<m && edges[j].w==edges[i].w) j++;
		for(int k=i;k<j;k++){
			int ru=dsu.find(edges[k].u), rv=dsu.find(edges[k].v);
			if(ru!=rv) ans[edges[k].id]="YES";
			else ans[edges[k].id]="NO";
		}
		for(int k=i;k<j;k++) dsu.unite(edges[k].u,edges[k].v);
		i=j;
	}
	for(int i=0;i<m;i++) cout<<ans[i]<<'\n';
	return 0;
}
