#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int mxn=2e5+1;
int sz[mxn];
int depth[mxn];
int par[mxn];
int val[mxn];
int id[mxn];
int tp[mxn];
int T[1<<20];
vector<int>g[200001];
int n,q,ct=1;
 
void upd(int i, int x){
	T[i+=n]=x;
	for(i>>=1;i;i>>=1)
		T[i]=max(T[i<<1],T[i<<1|1]);
}
 
int query(int l, int r){
	int res=0;
	for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
		if(l&1)
			res=max(res,T[l++]);
		if(r&1)
			res=max(res,T[--r]);
	}
	return res;
}
 
void dfs(int v=1, int e=1){
	sz[v]=1;
	par[v]=e;
	for(const int&i:g[v])
		if(i!=e){
			depth[i]=depth[v]+1;
			par[i]=v;
			dfs(i,v);
			sz[v]+=sz[i];
		}
}
 
void hld(int v=1, int e=1, int top=1){
	id[v]=ct++;
	tp[v]=top;
	upd(ct-1,val[v]);
	int hch=-1;
	int sch=-1;
	for(const int&i:g[v])
		if(i!=e)
			if(sz[i]>sch){
				sch=sz[i];
				hch=i;
			}
	if(hch==-1)
		return;
	hld(hch,v,top);
	for(const int&i:g[v])
		if(i!=e and i!=hch)
			hld(i,v,i);
}
 
int path(int a, int b){
	int res=0;
	while(tp[a]!=tp[b]){
		if(depth[tp[a]]<depth[tp[b]])
			swap(a,b);
		res=max(res,query(id[tp[a]],id[a]));
		a=par[tp[a]];
	}
	if(depth[a]>depth[b])
		swap(a,b);
	res=max(res,query(id[a],id[b]));
	return res;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>q;
	for(int i=1;i<=n;++i)
		cin>>val[i];
	for(int i=1,a,b;i<n;++i){
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs();
	hld();
	while(q--){
		int x,a,b;
		cin>>x>>a>>b;
		if(x==1){
			val[a]=b;
			upd(id[a],b);
		}
		else
			cout<<path(a,b)<<' ';
	}
}
