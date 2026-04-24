#include<bits/stdc++.h>
using namespace std;
using ll=long long;
 
map<vector<int>,int>mp;
int idx=0;
int dfs(int v, int e, vector<int>g[]){
	vector<int>s;
	for(const int& i:g[v])
		if(i!=e)
			s.push_back(dfs(i,v,g));
	sort(s.begin(),s.end());
	if(!mp.count(s))
		mp[s]=idx++;
	return mp[s];
}
int t,n;
int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>t;
	while(t--){
		cin>>n;
		vector<int> g1[n+1], g2[n+1];
		for(int i=1;i<n;++i){
			int a,b;
			cin>>a>>b;
			g1[a].push_back(b);
			g1[b].push_back(a);
		}
		for(int i=1;i<n;++i){
			int a,b;
			cin>>a>>b;
			g2[a].push_back(b);
			g2[b].push_back(a);
		}
		int s1=dfs(1,-1,g1);
		int s2=dfs(1,-1,g2);
		cout<<(s1==s2?"YES\n":"NO\n");
	}
}
