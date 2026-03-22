#include<bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int MAXS=1e6+5;
int last[MAXS];
int bit[MAXS];
int ma[MAXS];
vector<int>adj[MAXS];

int n;

void upd(int i, int x){
	for(;i<=n;i+=i&-i)
		bit[i]=max(bit[i],x);
}

int sum(int i){
	int ret=0;
	for(;i>0;i-=i&-i)
		ret=max(ret,bit[i]);
	return ret;
}

void dfs(int i, int len){
	if(len>ma[i]){
		ma[i]=len;
		upd(i,len);
		for(auto j:adj[i])
			dfs(j,len+1);
	}
}

void solve(){
	int m;
	cin>>n>>m;
	int ans[m+1];
	vector<pair<int,int>>q[n+1];
	vector<int>v;
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		v.push_back(x);
		int la=0;
		for(int j=x-1;j>=1;--j)
			if(last[j]>la){
				adj[last[j]].push_back(i);
				la=last[j];
			}
		last[x]=i;
	}
	for(auto&i:v)
		last[i]=0;
	for(int i=1;i<=m;++i){
		int a,b;
		cin>>a>>b;
		q[a].push_back({b,i});
	}
	for(int i=n;i>=1;--i){
		dfs(i,1);
		for(auto j:q[i])
			ans[j.second]=sum(j.first);
	}
	for(int i=1;i<=m;++i)
		cout<<ans[i]<<'\n';
	for(int i=1;i<=n;++i){
		adj[i].clear();
		bit[i]=0;
		ma[i]=0;
	}
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin>>t;
	while(t--)
		solve();
}
