#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using ar=array<int,2>;
int n,m;
vector<ar>g[100007];
vector<ar>edges;
bool used[200001];
int st[100007],low[100007];
int timer=1;
 
void dfs(int v){
	st[v]=low[v]=timer++;
	for(const auto&[i,id]:g[v])
		if(!used[id]){
			used[id]=1;
			if(edges[id][0]!=v)
				swap(edges[id][0],edges[id][1]);
			if(st[i])
				low[v]=min(low[v],st[i]);
			else{
				dfs(i);
				low[v]=min(low[v],low[i]);
				if(st[v]<low[i]){
					cout<<"IMPOSSIBLE";
					exit(0);
				}
			}
		}
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	edges.resize(m);
	for(int i=0,a,b;i<m;++i){
		cin>>a>>b;
		g[a].push_back({b,i});
		g[b].push_back({a,i});
		edges[i]={a,b};
	}
	int cnt=0;
	for(int i=1;i<=n;++i)
		if(!st[i]){
			if(cnt==1){
				cout<<"IMPOSSIBLE";
				exit(0);
			}
			dfs(i);
			++cnt;
		}
	for(int i=0;i<m;++i)
		cout<<edges[i][0]<<' '<<edges[i][1]<<'\n';
}
