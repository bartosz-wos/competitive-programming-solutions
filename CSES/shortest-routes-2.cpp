#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr ll inf = 1LL << 60;
ll g[501][501];
int n, m, q;
 
void floyd() {
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m >> q;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			if(i == j)
				g[i][j] = 0;
			else
				g[i][j] = inf;
		}
 
	while(m--) {
		ll a, b, w;
		cin >> a >> b >> w;
		g[a][b] = min(g[a][b], w);
		g[b][a] = min(g[b][a], w);
	}
 
	floyd();
	while(q--) {
		int a, b;
		cin >> a >> b;
		cout << (g[a][b] == inf ? -1 : g[a][b]) << '\n';
	}
}
