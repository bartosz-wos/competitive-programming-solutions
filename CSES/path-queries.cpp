#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int maxN = 2e5+1;
int n, q;
vector<int> g[maxN];
int st[maxN], en[maxN], val[maxN];
ll bit[maxN];
int timer = 1;
 
void upd(int i, int x) {
	for(; i <= n; i += i & -i)
		bit[i] += x;
}
 
ll query(int i) {
	ll ans = 0;
	for(; i; i -= i & -i)
		ans += bit[i];
	return ans;
}
 
void dfs(int v, int e) {
	st[v] = timer++;
	for(const int& i : g[v]) {
		if(i == e) continue;
		dfs(i, v);
	}
	en[v] = timer - 1;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i)
		cin >> val[i];
	for(int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, -1);
	for(int i = 1; i <= n; ++i) {
		upd(st[i], val[i]);
		upd(en[i] + 1, -val[i]);
	}
	while(q--) {
		int z, a, b;
		cin >> z;
		if(z == 1) {
			cin >> a >> b;
			upd(st[a], b - val[a]);
			upd(en[a] + 1, -(b - val[a]));
			val[a] = b;
		}
		else {
			cin >> a;
			cout << query(st[a]) << '\n';
		}
	}
}
