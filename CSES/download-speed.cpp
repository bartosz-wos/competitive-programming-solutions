#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, m;
set<int> g2[501];
ll g[501][501];
bitset<501> vis;
int par[501];
 
bool bfs() {
	vis.reset();
	queue<int> Q;
	Q.push(1);
	vis[1] = 1;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
 
		for(const int& i: g2[u])
			if(!vis[i])
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
		ll a, b, w;
		cin >> a >> b >> w;
		g[a][b] += w;
		g2[a].insert(b);
	}
 
	int u, v;
	ll maxflow = 0;
	while(bfs()) {
		ll flow = 1e18;
		for(v = n; v != 1; v = par[v]) {
			u = par[v];
			flow = min(flow, g[u][v]);
		}
		maxflow += flow;
		for(v = n; v != 1; v = par[v]) {
			u = par[v];
			g[u][v] -= flow;
			if(!g[u][v])
				g2[u].erase(v);
			g[v][u] += flow;
			if(g[v][u] - flow == 0)
				g2[v].insert(u);
		}
	}
	cout << maxflow;
}

