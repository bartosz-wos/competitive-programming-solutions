#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
int n, m;
int vis[100001];
vector<int> g[100001];
ll ans = 1;
 
int cnt;
ll exp(ll a, ll w) {
	ll ans = 1;
	a %= mod;
	while (w) {
		if (w & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		w >>= 1;
	}
	return ans;
}
 
void dfs(int v, int e) {
	vis[v] = 1;
	for (const int& i : g[v]) {
		if (i == e) continue;
		if (vis[i] == 1)
			++cnt;
		else if (!vis[i])
			dfs(i, v);
	}
	vis[v] = 2;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
 
	for(int i = 1; i <= n; ++i)
		if (!vis[i]) {
			cnt = 0;
			dfs(i, -1);
			ans = ans * exp(2, cnt) % mod;
		}
	cout << ans;
}
