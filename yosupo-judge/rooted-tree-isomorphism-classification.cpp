#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n;
vector<int>g[500005];
int ans[500005];
map<vector<int>,int>mp;
int id;

int dfs(int v, int e){
	vector<int>vec;
	for(const int&i:g[v]){
		if(i==e)continue;
		vec.push_back(dfs(i,v));
	}
	sort(vec.begin(),vec.end());
	if(!mp.count(vec))mp[vec]=++id;
	return ans[v]=mp[vec];
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n;
	for(int i=1,p;i<n;++i){
		cin>>p;
		g[p].push_back(i);
		g[i].push_back(p);
	}
	dfs(0,-1);
	cout<<mp.size()<<'\n';
	for(int i=0;i<n;++i)
		cout<<ans[i]-1<<' ';
}
