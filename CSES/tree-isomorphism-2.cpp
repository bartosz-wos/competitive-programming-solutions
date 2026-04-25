#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
map<vector<int>,int>mp;
 
int n;
void calc(int v, int e, int des, vector<vector<int>>&g, vector<int>&sz, vector<int>&c){
	sz[v]=1;
	bool ok=1;
	for(const int&i:g[v])
		if(i!=e){
			calc(i,v,des,g,sz,c);
			sz[v]+=sz[i];
			if(sz[i]>des)ok=0;
		}
	if(n-sz[v]>des)ok=0;
	if(ok)c.push_back(v);
}
 
int timer=0;
int dfs(int v,int e,vector<vector<int>>&g){
	vector<int>ch;
	for(const int&i:g[v])
		if(i!=e) ch.push_back(dfs(i,v,g));
	sort(ch.begin(),ch.end());
	if(!mp.count(ch))mp[ch]=++timer;
	return mp[ch];
}
 
void solve(){
	mp.clear();
	timer=0;
	cin>>n;
	vector<vector<int>>g1(n+1),g2(n+1);
	vector<int>c1,c2;
	vector<int>sz1(n+1,0),sz2(n+1,0);
	for(int i=1,a,b;i<n;++i){
		cin>>a>>b;
		g1[a].push_back(b);
		g1[b].push_back(a);
	}
	for(int i=1,a,b;i<n;++i){
		cin>>a>>b;
		g2[a].push_back(b);
		g2[b].push_back(a);
	}
	calc(1,0,n>>1,g1,sz1,c1);
	calc(1,0,n>>1,g2,sz2,c2);
	for(const int&i:c1)
		for(const int&j:c2)
			if(dfs(i,0,g1)==dfs(j,0,g2)){
				cout<<"YES\n";
				return;
			}
	cout<<"NO\n";
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;cin>>t;
	while(t--)solve();
}
