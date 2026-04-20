#include<bits/stdc++.h>
using namespace std;
vector<int> g[100001];
int n, m, timer = 1;
vector<array<int, 2>> ans;
bitset<100001> vis;
int st[100001], low[100001];
 
void dfs(int v, int e) {
	vis[v] = 1;
	st[v] = low[v] = timer++;
	for(const int& i : g[v]) {
		if(i == e) continue;
		if(vis[i]) 
			low[v] = min(low[v], st[i]);
		else {
			dfs(i, v);
			low[v] = min(low[v], low[i]);
			if(low[i] > st[v])
				ans.push_back({v, i});
		}
	}
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, -1);
	cout << ans.size() << '\n';
	for(const auto& [u, v] : ans)
		cout << u << ' ' << v << '\n';
}
