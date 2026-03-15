#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<int,2>;

constexpr int mod=998244353;
constexpr int inv2=mod+1>>1;

struct edge{
	int u,v,t;
};

int n,m;
ll x[500005];
int p[500005];
vector<pi>merges[500005];
int id[500005];

int fd(int x){
	return p[x]<0?x:p[x]=fd(p[x]);
}

void solve(int l, int r, const vector<edge>&edg){
	if(edg.empty())return;
	int mid=(l+r)>>1;
	vector<vector<edge>>lef;
	vector<edge>rig;
	{
		vector<int>v;
		for(const edge&e:edg){
			if(!~id[e.u]){
				id[e.u]=v.size();
				v.push_back(e.u);
			}
			if(!~id[e.v]){
				id[e.v]=v.size();
				v.push_back(e.v);
			}
		}
		vector<vector<int>>g(v.size()),rg(v.size());
		for(const edge&e:edg)
			if(l==r or e.t<=mid){
				g[id[e.u]].push_back(id[e.v]);
				rg[id[e.v]].push_back(id[e.u]);
			}
		vector<bool>vis(v.size(),0);
		vector<int>ord;
		ord.reserve(v.size());
		auto dfs1=[&](auto&self, int v)->void{
			vis[v]=1;
			for(const int&i:g[v])
				if(!vis[i])self(self,i);
			ord.push_back(v);
		};
		for(int i=0;i<v.size();++i)
			if(!vis[i])dfs1(dfs1,i);
		fill(vis.begin(),vis.end(),0);
		vector<int>scc_id(v.size(),-1);
		int cnt=0;
		auto dfs2=[&](auto&self, int v, int cid)->void{
			vis[v]=1;
			scc_id[v]=cid;
			for(const int&i:rg[v])
				if(!vis[i])self(self,i,cid);
		};
		reverse(ord.begin(),ord.end());
		for(const int&i:ord)
			if(!vis[i])dfs2(dfs2,i,cnt++);
		vector<int>par(cnt,-1);
		for(int i=0;i<v.size();++i)
			if(!~par[scc_id[i]])
				par[scc_id[i]]=v[i];
		if(l==r){
			for(int i=0;i<v.size();++i)
				if(v[i]!=par[scc_id[i]])
					merges[l].push_back({par[scc_id[i]],v[i]});
		}else{
			vector<int>lef_mp(cnt,-1);
			for(const edge&e:edg){
				int idu=scc_id[id[e.u]];
				int idv=scc_id[id[e.v]];
				if(idu==idv){
					if(e.t<=mid){
						if(!~lef_mp[idu]){
							lef_mp[idu]=lef.size();
							lef.emplace_back();
						}
						lef[lef_mp[idu]].push_back(e);
					}
				}else rig.push_back({par[idu],par[idv],e.t});
			}
			for(const int&i:v)id[i]=-1;
		}
		for(const int&i:v)id[i]=-1;
	}
	if(l<r){
		for(auto&lef2:lef){
			solve(l,mid,lef2);
			vector<edge>().swap(lef2);
		}
		vector<vector<edge>>().swap(lef);
		if(!rig.empty())solve(mid+1,r,rig);
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	ll sq=0,tot=0;
	for(int i=0;i<n;++i){
		cin>>x[i];
		tot=(tot+x[i]*x[i])%mod;
		p[i]=id[i]=-1;
	}
	vector<edge>edg(m);
	for(int i=0;i<m;++i){
		cin>>edg[i].u>>edg[i].v;
		edg[i].t=i+1;
	}
	solve(1,m,edg);
	sq=tot;
	for(int i=1;i<=m;++i){
		for(const auto&p2:merges[i]){
			int pu=fd(p2[0]),pv=fd(p2[1]);
			if(pu!=pv){
				sq=(sq-x[pu]*x[pu]%mod+mod)%mod;
				sq=(sq-x[pv]*x[pv]%mod+mod)%mod;
				x[pu]+=x[pv];
				if(x[pu]>=mod)x[pu]-=mod;
				sq+=x[pu]*x[pu]%mod;
				if(sq>=mod)sq-=mod;
				p[pv]=pu;
			}
		}
		cout<<(sq-tot+mod)%mod*inv2%mod<<'\n';
	}
}
