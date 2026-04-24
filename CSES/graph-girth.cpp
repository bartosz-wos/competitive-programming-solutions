#include<bits/stdc++.h>
using namespace std;
int n, m;
vector<int> g[2501];
 
int bfs(int v) {
	queue<int> Q;
	vector<int> dist(n + 1, -1);
	Q.push(v);
	dist[v] = 0;
	int ans = 1 << 30;
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(const int& i : g[u]) {
			if(dist[i] == -1) {
				dist[i] = dist[u] + 1;
				Q.push(i);
			}
			else if(dist[i] >= dist[u])
				ans = min(ans, dist[i] + dist[u] + 1);
		}
	}
	return ans;
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
	int ans = 1 << 30;
	for(int i = 1; i <= n; ++i)
		ans = min(ans, bfs(i));
	cout << (ans == (1 << 30) ? -1 : ans);
}
