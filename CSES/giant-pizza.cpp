#include<bits/stdc++.h>
using namespace std;
constexpr int maxn = 2e5+1;
int comp[maxn];
int ans[maxn];
int comps;
vector<int> g[maxn], rg[maxn];
vector<int> kos;
bitset<maxn> vis;
 
void dfs1(int v) {
	vis[v] = 1;
	for(const int& i : g[v])
		if(!vis[i])
			dfs1(i);
	kos.push_back(v);
}
 
void dfs2(int v) {
	vis[v] = 1;
	comp[v] = comps;
	for(const int& i : rg[v])
		if(!vis[i])
			dfs2(i);
}
 
void solve() {
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; ++i) {
		int a, b;
		char x, y;
		cin >> x >> a >> y >> b;
		if(x == '-')
			a = 2 * m - a + 1;
		if(y == '-')
			b = 2 * m - b + 1;
		g[2 * m - a + 1].push_back(b);
		g[2 * m - b + 1].push_back(a);
		rg[a].push_back(2 * m - b + 1);
		rg[b].push_back(2 * m - a + 1);
	}
	for(int i = 1; i <= (m << 1); ++i)
		if(!vis[i])
			dfs1(i);
	vis.reset();
 
	reverse(kos.begin(), kos.end());
	for(const int& i : kos)
		if(!vis[i])
			++comps, dfs2(i);
 
	for(int i = 1; i <= m; ++i) {
		if(comp[i] == comp[2 * m - i + 1]) {
			cout << "IMPOSSIBLE";
			return;
		}
		ans[i] = (comp[i] > comp[2 * m - i + 1]);
	}
	for(int i = 1; i <= m; ++i)
		cout << (ans[i] ? '+' : '-') << ' ';
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t = 1;
	while(t--)
		solve();
}
