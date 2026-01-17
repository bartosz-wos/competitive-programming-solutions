#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int B = 1000;

int n, m, q;

stack<int> stck;
int sz[100001], cmp[100001];

void reset() {
	iota(cmp + 1, cmp + 1 + n, 1);
	fill(sz + 1, sz + n + 1, 1);
}

inline int find(int a) {
	while (cmp[a] != a) a = cmp[a];
	return a;
}

void onion(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return;
	if (sz[a] > sz[b]) swap(a, b);
	stck.push(a);
	sz[b] += sz[a];
	cmp[a] = b;
}

void rollback(int x) {
	while (stck.size() > x) {
		int k = stck.top();
		stck.pop();
		sz[cmp[k]] -= sz[k];
		cmp[k] = k;
	}
}

int u[100001], v[100001], w[100001];
int t[100001], x[100001], y[100001];
bool changed[100001];
vector<int> to_join[B];
int ans[100001];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m;
	FOR(i, 1, m + 1) cin >> u[i] >> v[i] >> w[i];
	cin >> q;
	FOR(i, 1, q + 1) cin >> t[i] >> x[i] >> y[i];

	for (int l = 1; l <= q; l += B) {
		int r = min(q + 1, l + B);
		reset();
		fill(changed + 1, changed + m + 1, false);

		vector<int> ask, upd, unchanged;
		FOR(i, l, r) {
			if (t[i] == 1) {
				changed[x[i]] = true;
				upd.push_back(i);
			} else ask.push_back(i);
		}
		FOR(i, 1, m + 1) if (!changed[i]) unchanged.push_back(i);

		FOR(i, l, r) {
			if (t[i] == 1) w[x[i]] = y[i];
			else {
				to_join[i - l].clear();
				for (int j : upd)
					if (w[x[j]] >= y[i]) to_join[i - l].push_back(x[j]);
			}
		}

		sort(ask.begin(), ask.end(), [&](int a, int b) { return y[a] > y[b]; });
		sort(unchanged.begin(), unchanged.end(),
		     [&](int a, int b) { return w[a] > w[b]; });

		int ptr = 0;
		for (int i : ask) {
			while (ptr < unchanged.size() && w[unchanged[ptr]] >= y[i]) {
				onion(u[unchanged[ptr]], v[unchanged[ptr]]);
				ptr++;
			}
			int prev_size = stck.size();
			for (int j : to_join[i - l]) onion(u[j], v[j]);
			ans[i] = sz[find(x[i])];
			rollback(prev_size);
		}
	}

	FOR(i, 1, q + 1) if (t[i] == 2) cout << ans[i] << '\n';
}
