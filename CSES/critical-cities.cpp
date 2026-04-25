#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int maxn=1e5+1;
 
int n,m,p[maxn],sdom[maxn],idom[maxn],label[maxn];
int timer,st[maxn],inv[maxn],dsu[maxn];
vector<int>res,g[maxn],rg[maxn],dt[maxn],bucket[maxn];
 
void dfs(int v=1){
	st[v]=++timer;
	inv[timer]=v;
	label[timer]=sdom[timer]=dsu[timer]=timer;
	for(const int&i:g[v]){
		if(!st[i]){
			dfs(i);
			p[st[i]]=st[v];
		}
		rg[st[i]].push_back(st[v]);
	}
}
 
int find(int u, bool x=0){
	if(u==dsu[u])return x?-1:u;
	int v=find(dsu[u],1);
	if(v<0)return u;
	if(sdom[label[dsu[u]]]<sdom[label[u]])
		label[u]=label[dsu[u]];
	dsu[u]=v;
	return x?v:label[u];
}
 
void build(){
	dfs();
 
	for(int u=n;u>=1;--u){
		for(const int&v:rg[u])
			sdom[u]=min(sdom[u],sdom[find(v)]);
		if(u>1)bucket[sdom[u]].push_back(u);
		for(const int&i:bucket[u])
			idom[i]=(sdom[find(i)]==sdom[i]?sdom[i]:find(i));
		if(u>1)dsu[u]=p[u];
	}
	for(int u=2;u<=n;++u){
		if(idom[u]!=sdom[u])
			idom[u]=idom[idom[u]];
		dt[inv[u]].push_back(inv[idom[u]]);
		dt[inv[idom[u]]].push_back(inv[u]);
	}
}
 
bool dfs_dom_tree(int u=1,int p=0){
	bool ok=(u==n);
	for(const int&v:dt[u])
		if(v!=p)
			ok|=dfs_dom_tree(v,u);
	if(ok)res.push_back(u);
	return ok;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	while(m--){
		int a,b;
		cin>>a>>b;
		g[a].push_back(b);
	}
	build();
	dfs_dom_tree();
	sort(res.begin(),res.end());
	cout<<res.size()<<'\n';
	for(const int&i:res)cout<<i<<' ';
}
