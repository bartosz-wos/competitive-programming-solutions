#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n,m,k,cnt,mt[505];
vector<int>g[505];
vector<pair<int,int>>ans;
bool vis[505];
 
bool dfs(int v){
	if(vis[v])
		return false;
	vis[v]=1;
	for(const int&i:g[v])
		if(!mt[i] or dfs(mt[i])){
			mt[i]=v;
			return true;
		}
	return false;
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m>>k;
	while(k--){
		int a,b;
		cin>>a>>b;
		g[b].push_back(a);
	}
	for(int i=1;i<=m;++i){
		fill(vis+1,vis+n+1,false);
		dfs(i);
	}
	for(int i=1;i<=n;++i)
		if(mt[i]){
			ans.push_back({i,mt[i]});
			++cnt;
		}
	cout<<cnt<<'\n';
	for(const auto&[f,s]:ans)
		cout<<f<<' '<<s<<'\n';
}
