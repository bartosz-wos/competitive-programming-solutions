#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<ll,2>;
constexpr int maxn=1e5+1;
constexpr ll inf=1LL<<60;
 
const vector<int>mod{(int)1e9+7,1696969};
 
ll dist[maxn][2];
int path[maxn][2][2];
vector<ar>g[maxn][2];
vector<int>res;
 
void dijk(int v, bool f){
	dist[v][f]=0;
	for(int i=0;i<2;++i)
		path[v][f][i]=1;
	priority_queue<ar,vector<ar>,greater<ar>>Q;
	Q.push({0,v});
	while(!Q.empty()){
		int u=Q.top()[1];
		ll d=Q.top()[0];
		Q.pop();
		if(d>dist[u][f])continue;
		for(const auto&[i,w]:g[u][f]){
			if(dist[i][f]>d+w){
				dist[i][f]=d+w;
				for(int j=0;j<2;++j)
					path[i][f][j]=path[u][f][j];
				Q.push({d+w,i});
			}
			else if(dist[i][f]==dist[u][f]+w){
				for(int j=0;j<2;++j){
					ll p=path[i][f][j]+path[u][f][j];
					if(p>=mod[j])p-=mod[j];
					path[i][f][j]=p;
				}
			}
		}
	}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;++i)
		dist[i][0]=dist[i][1]=inf;
	while(m--){
		ll a,b,w;
		cin>>a>>b>>w;
		g[a][0].push_back({b,w});
		g[b][1].push_back({a,w});
	}
	dijk(1,0);
	dijk(n,1);
	for(int v=1;v<=n;++v){
		bool ok=1;
		if(dist[v][0]+dist[v][1]!=dist[n][0])continue;
		for(int j=0;j<2;++j){
			ll p=(ll)path[v][0][j]*(ll)path[v][1][j];
			p%=mod[j];
			if(p!=path[n][0][j])
				ok=0;
		}
		if(ok)res.push_back(v);
	}
	cout<<res.size()<<'\n';
	for(const int&i:res)cout<<i<<' ';
}
