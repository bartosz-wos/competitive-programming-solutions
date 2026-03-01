#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<ll,2>;

constexpr ll inf=1e18;

struct edge{
	int v,id;
	ll w;
};
struct full_edge{
	int u,v,id;
	ll w;
};

vector<edge>g[2005];
vector<full_edge>edges;
ll dist[2005][2005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	for(int i=0,u,v;i<m;++i){
		ll c;
		cin>>u>>v>>c;
		g[u].push_back({v,i,c});
		g[v].push_back({u,i,c});
		edges.push_back({u,v,i,c});	
	}
	if(n==1){
		cout<<0<<'\n';
		return 0;
	}
	memset(dist,-1,sizeof dist);
	for(int i=0;i<n;++i){
		dist[i][i]=0;
		priority_queue<pi,vector<pi>,greater<pi>>q;
		q.push({0,i});
		while(!q.empty()){
			auto[d,v]=q.top();
			q.pop();
			if(~dist[i][v] and d>dist[i][v])
				continue;
			for(const auto&e:g[v])
				if(!~dist[i][e.v] or (~dist[i][e.v] and dist[i][v]+e.w<dist[i][e.v])){
					dist[i][e.v]=dist[i][v]+e.w;
					q.push({dist[i][e.v],e.v});
				}
		}
	}
	ll minr=inf;
	int b_u,b_v,b_e;
	b_u=b_v=b_e=-1;
	ll b_x=0;
	for(int i=0;i<n;++i){
		ll md=0;
		for(int j=0;j<n;++j)
			md=max(md,dist[i][j]);
		if(md*2<minr){
			minr=md*2;
			b_u=i;
		}
	}
	for(const auto&e:edges){
		int u=e.u,v=e.v;
		ll w=e.w;
		int idx=e.id;
		vector<int>p(n);
		iota(p.begin(),p.end(),0);
		sort(p.begin(),p.end(),[&](int a, int b){
			if(dist[u][a]!=dist[u][b])return dist[u][a]>dist[u][b];
			return dist[v][a]>dist[v][b];
		});
		ll v_m=dist[v][p[0]];
		for(int i=1,c;i<n;++i){
			c=p[i];
			ll c_v=dist[v][c];
			if(c_v>v_m){
				ll x2=w+v_m-dist[u][c];
				if(x2>=0 and x2<=2*w){
					ll c_r=dist[u][c]+v_m+w;
					if(c_r<minr){
						minr=c_r;
						b_u=u;
						b_v=v;
						b_e=idx;
						b_x=x2;
					}
				}
				v_m=c_v;
			}
		}
	}

	vector<int>ans;
	if(!~b_e){
		vector<ll>d(n,inf);
		vector<int>pe(n,-1);
		priority_queue<pi,vector<pi>,greater<pi>>q;
		d[b_u]=0;
		q.push({0,b_u});
		while(!q.empty()){
			auto[cd,v]=q.top();
			q.pop();
			if(cd>d[v])continue;
			for(const auto&e:g[v])
				if(d[v]+e.w<d[e.v]){
					d[e.v]=d[v]+e.w;
					pe[e.v]=e.id;
					q.push({d[e.v],e.v});
				}
		}
		for(int i=0;i<n;++i)
			if(i!=b_u and pe[i]!=-1)
				ans.push_back(pe[i]);
	}else{
		vector<ll>d(n,inf);
		vector<int>pe(n,-1);
		priority_queue<pi,vector<pi>,greater<pi>>q;
		ll w=0;
		for(const auto&e:edges)
			if(e.id==b_e){
				w=e.w;
				break;
			}
		int v_u=-2,v_v=-3;
		d[b_u]=b_x;
		pe[b_u]=v_u;
		q.push({d[b_u],b_u});
		d[b_v]=2*w-b_x;
		pe[b_v]=v_v;
		q.push({d[b_v],b_v});
		while(!q.empty()){
			auto[cd,v]=q.top();
			q.pop();
			if(cd>d[v])continue;
			for(const auto&e:g[v])
				if(d[v]+e.w*2<d[e.v]){
					d[e.v]=d[v]+e.w*2;
					pe[e.v]=e.id;
					q.push({d[e.v],e.v});
				}
		}
		bool ok_u=0,ok_v=0;
		for(int i=0;i<n;++i){
			if(i==b_u and pe[i]==v_u)
				ok_u=1;
			else if(i==b_v and pe[i]==v_v)
				ok_v=1;
			else
				ans.push_back(pe[i]);
		}
		if(ok_u and ok_v)
			ans.push_back(b_e);
	}
	cout<<minr<<'\n';
	for(const int&i:ans)
		cout<<i<<' ';
	cout<<'\n';
}
