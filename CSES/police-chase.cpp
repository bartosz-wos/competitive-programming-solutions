#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m;
ll g[501][501], g2[501][501];
ll flow[501];
bitset<501> vis;
int par[501];
vector<array<int, 2>> ans;
 
bool reachable() {
	vis.reset();
	queue<int> Q;
	Q.push(1);
	vis[1] = 1;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(int i = 1; i <= n; ++i)
			if(g[u][i] && !vis[i])
				vis[i] = 1, par[i] = u, Q.push(i);
	}
	return vis[n];
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	while(m--) {
		ll a, b;
		cin >> a >> b;
		++g[a][b], ++g[b][a];
		++g2[a][b], ++g2[b][a];
	}
 
	int u, v;
	ll maxflow = 0;
	while(reachable()) {
		ll flow = 1e18;
		for(v = n; v != 1; v = par[v]) {
			u = par[v];
			flow = min(flow, g[u][v]);
		}
		maxflow += flow;
		for(v = n; v != 1; v = par[v]) {
			u = par[v];
			g[u][v] -= flow;
			g[v][u] += flow;
		}
	}
 
	reachable();
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			if(vis[i] && !vis[j] && g2[i][j]) ans.push_back({i, j});
 
	cout << ans.size() << '\n';
	for(const array<int, 2>& i : ans)
		cout << i[0] << ' ' << i[1] << '\n';
}
