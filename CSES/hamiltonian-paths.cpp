#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9+7;
vector<int> g[21];
int n, m;
int dp[21][1048577];
 
int hamPath(int v = 1, int mask = 0) {
	mask ^= (1 << v);
	if(v == n and mask == (1 << (n+1)) - 2)
		return 1;
	if(v == n)
		return 0;
	if(dp[v][mask])
		return dp[v][mask];
	dp[v][mask] = 0;
	for(const int& i : g[v])
		if(!( (1 << i) & mask ))
			dp[v][mask] = (dp[v][mask] + hamPath(i, mask)) % mod;
	return dp[v][mask];
}
 
void solve() {
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
	}
	cout << hamPath();
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t = 1;
	while(t--)
		solve();
}
