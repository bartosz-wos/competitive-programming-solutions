#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using edge=array<ll,3>;
using pi=array<ll,2>;

constexpr ll inf=1e18;

vector<edge>g[105];
ll dp[1<<12][105];
int pt[1<<12][105];
int pv[1<<12][105];
int pe[1<<12][105];

set<int>ids;
void get(int msk, int v){
	if(!pt[msk][v])return;
	if(pt[msk][v]==1){
		get(msk^pv[msk][v],v);
		get(pv[msk][v],v);
	}else if(pt[msk][v]==2){
		ids.insert(pe[msk][v]);
		get(msk,pv[msk][v]);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m,k;
	cin>>n>>m;
	for(ll i=0,a,b,c;i<m;++i){
		cin>>a>>b>>c;
		g[a].push_back({b,c,i});
		g[b].push_back({a,c,i});
	}
	cin>>k;
	vector<int>p(k);
	for(int&i:p)cin>>i;
	for(int i=0;i<1<<k;++i)
		fill(dp[i],dp[i]+n,inf);
	for(int i=0;i<k;++i)
		dp[1<<i][p[i]]=0;

	for(int msk=1;msk<1<<k;++msk){
		for(int i=0;i<n;++i)
			for(int sub=(msk-1)&msk;sub;sub=(sub-1)&msk){
				ll c=dp[sub][i]+dp[msk^sub][i];
				if(c<dp[msk][i]){
					dp[msk][i]=c;
					pt[msk][i]=1;
					pv[msk][i]=sub;
				}
			}
		priority_queue<pi,vector<pi>,greater<pi>>q;
		for(int i=0;i<n;++i)
			if(dp[msk][i]!=inf)
				q.push({dp[msk][i],i});
		while(!q.empty()){
			auto[d,v]=q.top();
			q.pop();
			if(d>dp[msk][v])continue;
			for(const edge&e:g[v]){
				if(dp[msk][v]+e[1]<dp[msk][e[0]]){
					dp[msk][e[0]]=dp[msk][v]+e[1];
					pt[msk][e[0]]=2;
					pv[msk][e[0]]=v;
					pe[msk][e[0]]=e[2];
					q.push({dp[msk][e[0]],e[0]});
				}
			}
		}
	}
	ll res=inf;
	int s=-1;
	for(int i=0;i<n;++i)
		if(dp[(1<<k)-1][i]<res){
			res=dp[(1<<k)-1][i];
			s=i;
		}
	get((1<<k)-1,s);
	cout<<res<<' '<<ids.size()<<'\n';
	for(const int&i:ids)
		cout<<i<<' ';
	cout<<'\n';
}
