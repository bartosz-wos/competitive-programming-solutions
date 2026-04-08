#include<iostream>
#include<vector>
#include<bitset>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
vector<int> g[200007];
bitset<200007> vis;
 
int ans;
void dfs(int v, int e) {
	for (const int& i : g[v]) {
		if (i == e) continue;
		dfs(i, v);
		if (!vis[i] && !vis[v])
			vis[i] = vis[v] = 1, ++ans;
	}
}
 
int n, m, a, b;
int main() {
	ios;
	cin >> n;
	for (int i = 1; i < n; ++i) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, -1);
	cout << ans;
}
