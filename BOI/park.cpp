#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using vi = vector<int>;
#define pb push_back
#define rsz resize
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

using pi = pair<int, int>;
#define f first
#define s second
#define mp make_pair

const int MX = 2006;

vector<pair<ll, pair<pi, pi>>> ed;
map<pi, int> cc;

template <int SZ> struct DSU {
	int p[SZ], sz[SZ];
	void init() {
		for (int i = 0; i < SZ; i++) {
			p[i] = i;
			sz[i] = 1;
		}
	}
	int find(int x) { return p[x] = (p[x] == x ? x : find(p[x])); }
	void merge(int u, int v) {
		int a = find(u);
		int b = find(v);
		if (a != b) {
			if (sz[a] < sz[b]) { swap(a, b); }
			p[b] = a;
			sz[a] += sz[b];
		}
	}
};

DSU<MX> dsu;
bool ok[100005][4];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, w, h;
	cin >> n >> m >> w >> h;
	vector<pair<pair<ll, ll>, int>> trees(n);
	set<pi> pts;
	auto dist = [&](int x1, int y1, int x2, int y2) {
		return sqrt((1LL * (x2 - x1) * (x2 - x1)) +
		            (1LL * (y2 - y1) * (y2 - y1)));
	};
	auto add = [&](int x1, int y1, int x2, int y2, ll r1, ll r2) {
		ll ndist = dist(x1, y1, x2, y2) - r1 - r2;
		ed.pb(mp(ndist, mp(mp(x1, y1), mp(x2, y2))));
	};
	for (int i = 0; i < n; i++) {
		cin >> trees[i].f.f >> trees[i].f.s >> trees[i].s;
		pts.insert(mp(trees[i].f.f, trees[i].f.s));
		cc[mp(0, trees[i].f.s)] = 3;
		cc[mp(trees[i].f.f, h)] = 2;
		cc[mp(w, trees[i].f.s)] = 1;
		cc[mp(trees[i].f.f, 0)] = 0;
		add(trees[i].f.f, trees[i].f.s, 0, trees[i].f.s, trees[i].s, 0);
		add(trees[i].f.f, trees[i].f.s, trees[i].f.f, 0, trees[i].s, 0);
		add(trees[i].f.f, trees[i].f.s, w, trees[i].f.s, trees[i].s, 0);
		add(trees[i].f.f, trees[i].f.s, trees[i].f.f, h, trees[i].s, 0);
	}
	int cnt = 4;
	for (pi x : pts) { cc[x] = cnt++; }
	assert(cnt <= n + 4);
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			add(trees[i].f.f, trees[i].f.s, trees[j].f.f, trees[j].f.s,
			    trees[i].s, trees[j].s);
		}
	}
	vector<pair<pi, int>> qrs;
	for (int i = 0; i < m; i++) {
		int r, e;
		cin >> r >> e;
		e--;
		qrs.pb(mp(mp(2 * r, e), i));
	}
	sort(all(qrs));
	sort(all(ed));
	dsu.init();
	int p = 0;
	memset(ok, true, sizeof(ok));
	for (auto v : ed) {
		while (p < sz(qrs) && qrs[p].f.f <= v.f) {
			bool conn[4][4];
			pair<pi, int> curr = qrs[p];
			for (int i = 0; i < 4; i++) {
				conn[i][i] = true;
				for (int j = i + 1; j < 4; j++) {
					conn[i][j] = (dsu.find(i) == dsu.find(j));
					conn[j][i] = conn[i][j];
				}
			}
			auto bad = [&](const int &x) {
				return conn[(x - 1 < 0 ? 3 : x - 1)][x];
			};
			for (int i = 0; i < 4; i++) {
				if (curr.f.s == i) { continue; }
				if (bad(curr.f.s) || bad(i)) {
					ok[curr.s][i] = false;
					continue;
				}
				bool upok = conn[0][2];
				bool sok = conn[1][3];
				if (abs(curr.f.s - i) == 2) {
					if (upok || sok) {
						ok[curr.s][i] = false;
						continue;
					}
				} else if (curr.f.s + i == 3) {
					if (sok) {
						ok[curr.s][i] = false;
						continue;
					}
				} else {
					if (upok) { ok[curr.s][i] = false; }
				}
			}
			++p;
			if (p >= sz(qrs)) break;
		}
		dsu.merge(cc[v.s.f], cc[v.s.s]);
	}
	for (int i = 0; i < m; i++) {
		string ret = "";
		for (int j = 0; j < 4; j++) {
			if (ok[i][j]) ret += to_string(j + 1);
		}
		cout << ret << '\n';
	}
}
