#include<iostream>
#include<array>
#include<vector>
using namespace std;
using ll = long long;
 
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define ar array
 
constexpr ll inf = 1LL << 60;
vector<ar<int, 3>> g;
vector<ll> dist(2507, inf);
vector<int> par(2507, 0);
 
int n, m, f;
int main() {
	ios;
	cin >> n >> m;
	g.resize(m);
	for (int i = 0; i < m; ++i)
		cin >> g[i][0] >> g[i][1] >> g[i][2];
 
	dist[1] = 0;
	int u, v, w;
	for (int i = 1; i <= n; ++i) {
		f = 0;
		for (const ar<int, 3>&i : g) {
			u = i[0], v = i[1], w = i[2];
			if (dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				par[v] = u;
				f = v;
			}
		}
	}
	if (!f) cout << "NO";
	else {
		cout << "YES\n";
		for (int i = 1; i <= n; ++i) f = par[f];
		vector<int> cycle;
		for (int x = f;; x = par[x]) {
			cycle.push_back(x);
			if (x == f && cycle.size() > 1) break;
		}
		for (int i = cycle.size() - 1; i >= 0; --i)
			cout << cycle[i] << ' ';
	}
}
