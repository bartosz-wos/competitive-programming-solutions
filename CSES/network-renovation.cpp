#include<bits/stdc++.h>
using namespace std;
using ll=long long;
int n;
vector<int>g[100001];
vector<int>res;
 
void dfs(int v, int e){
	for(const int&i:g[v])
		if(i!=e)
			dfs(i,v);
	if(g[v].size()==1)
		res.push_back(v);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1,a,b;i<n;++i){
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1,-1);
	int cnt=res.size();
	if(cnt&1)
		res.push_back(res[0]),++cnt;
	cout<<cnt/2<<'\n';
	for(int i=0;2*i<cnt;++i)
		cout<<res[i]<<' '<<res[i+cnt/2]<<'\n';
}
