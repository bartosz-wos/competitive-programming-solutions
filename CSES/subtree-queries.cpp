#include<iostream>
#include<vector>
using namespace std;
using ll = long long;
int n, q, timer = 1;
int w[200001];
int st[200001], en[200001];
ll T[200001];
vector<int> g[200001];
 
void upd(int v, int val) {
	for (; v <= n; v += v & -v)
		T[v] += val;
}
 
ll query(int a, int b) {
	ll ans = 0;
	for (; b; b -= b & -b)
		ans += T[b];
	--a;
	for (; a; a -= a & -a)
		ans -= T[a];
	return ans;
}
 
void change(int v, int val) {
	val -= query(v, v);
	upd(v, val);
}
 
void dfs(int v, int e) {
	st[v] = timer++;
	for (const int& i : g[v]) {
		if (i == e) continue;
		dfs(i, v);
	}
	en[v] = timer - 1;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> w[i];
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, -1);
	for (int i = 1; i <= n; ++i)
		upd(st[i], w[i]);
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int a, b;
			cin >> a >> b;
			change(st[a], b);
		}
		else {
			int a;
			cin >> a;
			cout << query(st[a], en[a]) << '\n';
		}
	}
}
