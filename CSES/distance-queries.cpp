#include<iostream>
#include<vector>
using namespace std;
int n, q;
int depth[200001];
int ptr[200001][20];
vector<int> g[200001];
 
void dfs(int v) {
	for (int i = 1; i < 20; ++i)
		ptr[v][i] = ptr[ptr[v][i - 1]][i - 1];
 
	for (const int& i : g[v]) {
		if (i == ptr[v][0]) continue;
		depth[i] = depth[ptr[i][0] = v] + 1;
		dfs(i);
	}
}
 
int jump(int v, int k) {
	int j = 0;
	while (k) {
		if (k & 1)
			v = ptr[v][j];
		k >>= 1;
		++j;
	}
	return v;
}
 
int lca(int a, int b) {
	if (depth[a] < depth[b])
		swap(a, b);
	a = jump(a, depth[a] - depth[b]);
	if (a == b)
		return a;
 
	for (int i = 19; i >= 0; --i) {
		int at = ptr[a][i], bt = ptr[b][i];
		if (at != bt)
			a = at, b = bt;
	}
	return ptr[a][0];
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q;
	for (int i = 2; i <= n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1);
	ptr[1][0] = 1;
	while (q--) {
		int a, b;
		cin >> a >> b;
		int l = lca(a, b);
		cout << depth[a] + depth[b] - 2 * depth[l] << '\n';
	}
}
