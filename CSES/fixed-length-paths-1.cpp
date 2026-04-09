#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
int n,k;
ll ans;
int sub[200001];
int cnt[200001]{1};
int mx_depth;
bitset<200001> used;
vector<int>g[200001];
 
int get_sz(int v, int e=-1){
	sub[v]=1;
	for(const int& i:g[v])
		if(!used[i] and i!=e)
			sub[v]+=get_sz(i,v);
	return sub[v];
}
 
int get_c(int v, int e, int des){
	for(const int& i:g[v])
		if(!used[i] and i!=e and sub[i]>des)
			return get_c(i,v,des);
	return v;
}
 
void get_cnt(int v, int e, bool filling, int depth=1){
	if(depth>k)
		return;
	mx_depth=max(mx_depth,depth);
	if(filling)
		++cnt[depth];
	else
		ans+=cnt[k-depth];
	for(const int& i:g[v])
		if(!used[i] and i!=e)
			get_cnt(i,v,filling,depth+1);
}
 
void decomp(int v=1){
	int c=get_c(v,-1,get_sz(v,-1)>>1);
	used[c]=1;
	mx_depth=0;
	for(const int& i:g[c])
		if(!used[i]){
			get_cnt(i,c,0);
			get_cnt(i,c,1);
		}
	for(int i=1;i<=mx_depth;++i)
		cnt[i]=0;
	for(const int& i:g[c])
		if(!used[i])
			decomp(i);
}
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>k;
	for(int i=1;i<n;++i){
		int a,b;
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	decomp();
	cout<<ans;
}
