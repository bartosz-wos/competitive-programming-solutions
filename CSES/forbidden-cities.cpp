#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int maxn=2e5+5;
 
int n,m,q;
int tr=1;
int bcc=0;
bool vis[maxn];
int st[maxn];
int low[maxn];
vector<int>g[maxn],b[maxn];
stack<int>S;
int d[maxn];
int ptr[maxn][20];
 
void dfs1(int v, int e){
	vis[v]=1;
	st[v]=low[v]=tr++;
	S.push(v);
	for(const int&i:g[v])
		if(i!=e){
			if(vis[i])
				low[v]=min(low[v],st[i]);
			else{
				dfs1(i,v);
				low[v]=min(low[v],low[i]);
				if(low[i]>=st[v]){
					b[v].push_back(++bcc);
					do b[bcc].push_back(S.top()),S.pop();
					while(b[bcc].back()!=i);
				}
			}
		}
}
 
void dfs2(int v, int e){
	for(const int&i:b[v])
		if(i!=e){
			d[i]=d[v]+1;
			ptr[i][0]=v;
			dfs2(i,v);
		}
}
 
int jump(int v, int k){
	int j=0;
	while(k){
		if(k&1)
			v=ptr[v][j];
		++j;
		k>>=1;
	}
	return v;
}
 
int lca(int a, int b){
	if(d[b]>d[a])
		swap(a,b);
	a=jump(a,d[a]-d[b]);
	if(a==b) return a;
	for(int i=19;i>=0;--i)
		if(ptr[a][i]!=ptr[b][i])
			a=ptr[a][i],b=ptr[b][i];
	return ptr[a][0];
}
 
int dist(int a, int b){
	return d[a]+d[b]-2*d[lca(a,b)];
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m>>q;
	bcc=n;
	while(m--){
		int x,y;
		cin>>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;++i)
		if(!st[i])dfs1(i,0);
	for(int i=1;i<=bcc;++i)
		if(!d[i])dfs2(i,0);
	for(int i=1;i<20;++i)
		for(int j=1;j<=bcc;++j)
			ptr[j][i]=ptr[ptr[j][i-1]][i-1];
	while(q--){
		int a,b,c;
		cin>>a>>b>>c;
		bool ok=dist(a,b)==dist(a,c)+dist(c,b);
		cout<<(ok?"NO\n":"YES\n");
	}
}
