#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll n, m, N, ans, sz[200001];
vector<int> graph[100001], bcc_graph[200001], stck;
int low[100001], tin[100001], timer = 1, bccs = 1;

void dfs(int node, int parent = 0) {
	low[node] = tin[node] = timer++;
	stck.push_back(node);
	N++;
	for (int i : graph[node])
		if (i != parent) {
			if (tin[i]) low[node] = min(low[node], tin[i]);
			else {
				dfs(i, node);
				low[node] = min(low[node], low[i]);
				if (low[i] >= tin[node]) {
					bcc_graph[node].push_back(n + bccs);
					while (!bcc_graph[n + bccs].size() ||
					       bcc_graph[n + bccs].back() != i) {
						bcc_graph[n + bccs].push_back(stck.back());
						stck.pop_back();
					}
					bccs++;
				}
			}
		}
}

void dfs2(int node) {
	sz[node] = (node <= n);
	for (int i : bcc_graph[node]) {
		dfs2(i);
		sz[node] += sz[i];
		if (node > n) ans -= bcc_graph[node].size() * sz[i] * (sz[i] - 1);
	}
	if (node > n) ans -= bcc_graph[node].size() * (N - sz[node]) * (N - sz[node] - 1);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	while (m--) {
		int u, v;
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	FOR(i, 1, n + 1) if (!tin[i]) {
		N = 0;
		dfs(i);
		ans += N * (N - 1) * (N - 2);
		dfs2(i);
	}
	cout << ans;
	return 0;
}
