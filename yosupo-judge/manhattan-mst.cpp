#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<ll,2>;

struct DSU{
	vector<int>p;
	DSU(int n){
		p.resize(n,-1);
	}
	int fd(int x){
		return p[x]<0?x:p[x]=fd(p[x]);
	}
	bool unite(int a, int b){
		a=fd(a);
		b=fd(b);
		if(a==b)return 0;
		p[a]+=p[b];
		p[b]=a;
		return 1;
	}
};

vector<vector<ll>>get_edges(vector<pi>&pts){
	vector<int>ids(pts.size());
	iota(ids.begin(),ids.end(),0);
	vector<vector<ll>>edges;
	for(int rot=0;rot<4;++rot){
		sort(ids.begin(),ids.end(),[&](int i, int j){
			return pts[i][0]+pts[i][1]<pts[j][0]+pts[j][1];
		});
		map<int,int,greater<int>>active;
		for(auto i:ids){
			for(auto it=active.lower_bound(pts[i][0]);it!=active.end();active.erase(it++)){
				int j=it->second;
				if(pts[i][0]-pts[i][1]>pts[j][0]-pts[j][1])break;
				edges.push_back({pts[i][0]-pts[j][0]+pts[i][1]-pts[j][1],i,j});
			}
			active[pts[i][0]]=i;
		}
		for(auto&p:pts){
			if(rot&1)p[0]*=-1;
			else swap(p[0],p[1]);
		}
	}
	return edges;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	vector<pi>a(n);
	for(auto&[x,y]:a)
		cin>>x>>y;
	auto v=get_edges(a);
	sort(v.begin(),v.end());
	vector<pi>ans;
	ll cost=0;
	DSU dsu(n);
	for(const auto&x:v)
		if(dsu.unite(x[1],x[2])){
			cost+=x[0];
			ans.push_back({x[1],x[2]});
		}
	cout<<cost<<'\n';
	for(const auto&[x,y]:ans)
		cout<<x<<' '<<y<<'\n';
}
