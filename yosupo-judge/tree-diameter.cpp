#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=pair<int,int>;

int n;
vector<pi>g[500005];

int lst=-1;
ll md=0;

void dfs(int v, int e, ll d){
	if(d>md){
		md=d;
		lst=v;
	}
	for(const auto&[u,w]:g[v]){
		if(u==e)continue;
		dfs(u,v,d+w);
	}
}

vector<int>path;

bool dfs_path(int v, int e, int t){
	path.push_back(v);
	if(v==t)return 1;
	for(const auto&[u,w]:g[v]){
		if(u==e)continue;
		if(dfs_path(u,v,t))return 1;
	}
	path.pop_back();
	return 0;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n;
	cin>>n;
	for(int i=1,a,b,c;i<n;++i){
		cin>>a>>b>>c;
		g[a].push_back({b,c});
		g[b].push_back({a,c});
	}
	dfs(1,-1,0);
	int lst2=lst;
	md=0;
	dfs(lst,-1,0);
	cout<<md<<' ';
	dfs_path(lst,-1,lst2);
	cout<<path.size()<<'\n';
	for(const int&i:path)cout<<i<<' ';
}
