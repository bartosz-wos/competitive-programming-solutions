#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
int n;
vector<int> g[200001];
ll dp[200001], ans[200001];
 
void dfs1(int v, int e, int d) {
	ans[1] += d;
	dp[v] = 1;
	for (const int& i : g[v]) {
		if (i == e) continue;
		dfs1(i, v, d + 1);
		dp[v] += dp[i];
	}
}
 
void dfs2(int v, int e) {
	for (const int& i : g[v]) {
		if (i == e) continue;
		ans[i] = ans[v] + n - 2 * dp[i];
		dfs2(i, v);
	}
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
 
	dfs1(1, -1, 0);
	dfs2(1, -1);
	for (int i = 1; i <= n; ++i)
		cout << ans[i] << ' ';
}
