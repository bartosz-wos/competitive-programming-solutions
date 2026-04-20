#include<iostream>
#include<bitset>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int n, m, q;
vector<vector<int>> g, reg;
vector<int> kos, comp;
bitset<50001> vis;
bitset<50001> dp[50001];
vector<vector<int>> adj;
 
void dfs(int v, const vector<vector<int>>& q) {
	vis[v] = 1;
	for (const int& i : q[v])
		if (!vis[i])
			dfs(i, q);
	kos.push_back(v);
}
 
void dfs2(int v, int e) {
	comp[v] = e;
	for (const int& i : reg[v])
		if (comp[i] == -1)
			dfs2(i, e);
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m >> q;
	g.resize(n + 1);
	reg.resize(n + 1);
	comp.resize(n + 1, -1);
	adj.resize(n + 1);
	while (m--) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		reg[b].push_back(a);
	}
 
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			dfs(i, g);
	reverse(kos.begin(), kos.end());
	for (const int& i : kos)
		if (comp[i] == -1)
			dfs2(i, i);
 
	for (int i = 1; i <= n; ++i)
		for (const int& j : g[i])
			if (comp[i] != comp[j])
				adj[comp[i]].push_back(comp[j]);
 
	vis.reset();
	kos.clear();
 
	for (int i = 1; i <= n; ++i)
		if (!vis[i])
			dfs(i, adj);
 
	for (const int& i : kos) {
		dp[i][i] = 1;
		for (const int& j : adj[i])
			dp[i] |= dp[j];
	}
 
	while (q--) {
		int a, b;
		cin >> a >> b;
		cout << (dp[comp[a]][comp[b]] ? "YES\n" : "NO\n");
	}
}
