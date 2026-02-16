#include<bits/stdc++.h>
using namespace std;
using ll=long long;

set<int>g[500005];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,m;
	cin>>n>>m;
	while(m--){
		int a,b;
		cin>>a>>b;
		g[a].insert(b);
		g[b].insert(a);
	}
	set<int>vis;
	for(int i=0;i<n;++i)
		vis.insert(i);
	vector<vector<int>>comps;
	while(!vis.empty()){
		int s=*vis.begin();
		vis.erase(s);
		vector<int>comp;
		queue<int>q;
		q.push(s);
		comp.push_back(s);
		while(!q.empty()){
			int u=q.front();
			q.pop();
			vector<int>nxt;
			for(const int&i:vis)
				if(!g[u].count(i))
					nxt.push_back(i);
			for(const int&i:nxt){
				vis.erase(i);
				comp.push_back(i);
				q.push(i);
			}
		}
		comps.push_back(comp);
	}
	cout<<comps.size()<<'\n';
	for(const auto&comp:comps){
		cout<<comp.size()<<' ';
		for(const int&i:comp)
			cout<<i<<' ';
		cout<<'\n';
	}
}
