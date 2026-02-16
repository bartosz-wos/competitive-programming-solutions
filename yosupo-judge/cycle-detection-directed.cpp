#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using pi=array<int,2>;

int n,m;
vector<pi>g[500005];
int on[500005];
int parn[500005];
int pare[500005];

vector<int>ids;

void dfs(int v, int e){
	on[v]=1;
	parn[v]=e;
	for(const auto&[u,id]:g[v]){
		if(on[u]==1){
			ids.push_back(id);
			while(v!=u){
				ids.push_back(pare[v]);
				v=parn[v];
			}
			cout<<ids.size()<<'\n';
			for(auto it=ids.rbegin();it!=ids.rend();++it)
				cout<<*it<<'\n';
			exit(0);
		}else if(!on[u]){
			pare[u]=id;
			dfs(u,v);
		}	
	}
	on[v]=2;
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i=0,a,b;i<m;++i){
		cin>>a>>b;
		g[a].push_back({b,i});
	}
	for(int i=0;i<n;++i)
		if(!on[i])
			dfs(i,-1);
	cout<<-1<<'\n';
}
