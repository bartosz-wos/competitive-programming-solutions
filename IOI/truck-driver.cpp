#include "deliveries.h"
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define BIT(x, i) ((x) >> (i) & 1)
#define MASK(i) (1LL << (i))
#define left ___left
#define right ___right
#define ALL(v) (v).begin(), (v).end()
#define REP(i, n) for (int i = 0, _n = (n); i < _n; ++i)
#define REPD(i, n) for (int i = (n); i-- > 0; )
#define FOR(i, a, b) for (int _b = (b), i = (a); i < _b; ++i)
#define FORD(i, b, a) for (int _a = (a), i = (b); i-- > _a; )
#define FORE(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORDE(i, b, a) for (int i = (b), _a = (a); i >= _a; --i)
#define scan_op(...) istream & operator >> (istream &in, __VA_ARGS__ &u)
#define print_op(...) ostream & operator << (ostream &out, const __VA_ARGS__ &u)
#define file(name) if (fopen(name".inp", "r")) { freopen(name".inp", "r", stdin); freopen(name".out", "w", stdout); }

template <class U, class V> scan_op(pair <U, V>) { return in >> u.fi >> u.se; }
template <class T> scan_op(vector <T>) { for (T &x: u) in >> x; return in; }
template <class U, class V> print_op(pair <U, V>) { return out << "(" << u.fi << ", " << u.se << ")"; }
template <size_t i, class T> ostream & print_tuple_utils(ostream &out, const T &tup) { if constexpr(i == tuple_size<T>::value) return out << ")"; else return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); }
template <class ...U> print_op(tuple <U...>) { return print_tuple_utils<0, tuple <U...>> (out, u); }
template <class Con, class = decltype(begin(declval<Con>()))> typename enable_if <!is_same<Con, string>::value, ostream &>::type operator << (ostream &out, const Con &u) { out << "{"; for (auto it = u.begin(); it != u.end(); ++it) out << (it == u.begin() ? "" : ", ") << *it; return out << "}"; }

struct Fenwick {
	vector <long long> bit;
	int N;
	Fenwick(int n = 0) {
		N = n;
		bit.resize(N + 1, 0);
	}
	void update(int i, long long val) {
		for (; i <= N; i += i & -i) bit[i] += val;
	}
	void update(int l, int r, long long val) {
		update(l, val);
		update(r + 1, -val);
	}
	long long get(int i) {
		long long res = 0;
		for (; i > 0; i &= i - 1) res += bit[i];
		return res;
	}
	long long get(int l, int r) {
		return get(r) - get(l - 1);
	}
	int lower_bound(long long val) {
		int res = 0;
		REPD(i, __lg(N) + 1) if ((res ^ MASK(i)) <= N && val > bit[res ^ MASK(i)]) {
			res ^= MASK(i);
			val -= bit[res];
		}
		return res + 1;
	}
};

const int MAX = 1e5 + 5;
const int LOG = 17;

int N, W[MAX], tin[MAX], tout[MAX], anc[MAX][LOG], T[MAX], timeDfs, depth[MAX], pos[MAX], treeSize[MAX];
long long length[MAX];
vector <pair <int, int>> adj[MAX];
long long sum_all, t_res;
Fenwick sum;

void dfs(int u) {
	tin[u] = ++timeDfs;
	pos[timeDfs] = u;
	FOR(i, 1, LOG) anc[u][i] = anc[anc[u][i - 1]][i - 1];
	depth[u] = depth[anc[u][0]] + 1;
	treeSize[u] = 1;
	for (auto [t, v]: adj[u]) if (v != anc[u][0]) {
		T[v] = t;
		anc[v][0] = u;
		length[v] = length[u] + t;
		dfs(v);
		treeSize[u] += treeSize[v];
	}	
	tout[u] = timeDfs;
}

int headHLD[MAX], depthHLD[MAX], posHLD[MAX], numBase, inv_posHLD[MAX];

void hld(int u) {
	posHLD[u] = ++numBase;
	inv_posHLD[numBase] = u;
	int heavy = -1;
	for (auto [t, v]: adj[u]) if (v != anc[u][0] && (heavy == -1 || treeSize[heavy] < treeSize[v])) heavy = v;
	if (heavy != -1) {
		headHLD[heavy] = headHLD[u];
		depthHLD[heavy] = depthHLD[u];
		hld(heavy);
	}
	for (auto [t, v]: adj[u]) if (v != anc[u][0] && v != heavy) {
		headHLD[v] = v;
		depthHLD[v] = depthHLD[u] + 1;
		hld(v);
	}
}

long long st[MAX << 2], lazy[MAX << 2];

void pushDown(int i, int l, int r) {
	int m = l + r >> 1;
	if (lazy[i]) {
		st[i << 1] += lazy[i] * (length[inv_posHLD[m]] - length[anc[inv_posHLD[l]][0]]);
		lazy[i << 1] += lazy[i];
		st[i << 1 | 1] += lazy[i] * (length[inv_posHLD[r]] - length[anc[inv_posHLD[m + 1]][0]]);
		lazy[i << 1 | 1] += lazy[i];
		lazy[i] = 0;
	}
}

void update(int i, int l, int r, int u, int v, int val) {
	if (l > v || r < u) return;
	if (u <= l && r <= v) {
		st[i] += val * (length[inv_posHLD[r]] - length[anc[inv_posHLD[l]][0]]);
		lazy[i] += val;
		return;
	}
	int m = l + r >> 1;
	pushDown(i, l, r);
	update(i << 1, l, m, u, v, val);
	update(i << 1 | 1, m + 1, r, u, v, val);
	st[i] = st[i << 1] + st[i << 1 | 1];
}

long long get(int i, int l, int r, int u, int v) {
	if (l > v || r < u) return 0;
	if (u <= l && r <= v) return st[i];
	int m = l + r >> 1;
	pushDown(i, l, r);
	return get(i << 1, l, m, u, v) + get(i << 1 | 1, m + 1, r, u, v);
}

void update(int u, int add) {
	while (headHLD[u]) {
		update(1, 1, N, posHLD[headHLD[u]], posHLD[u], add);
		u = anc[headHLD[u]][0];
	}
	update(1, 1, N, posHLD[0], posHLD[u], add);
}

long long get(int u) {
	long long res = 0;
	while (headHLD[u]) {
		res += get(1, 1, N, posHLD[headHLD[u]], posHLD[u]);
		u = anc[headHLD[u]][0];
	}
	res += get(1, 1, N, posHLD[0], posHLD[u]);
	return res;
}

void init(int _N, vector <int> U, vector <int> V, vector <int> T, vector <int> _W) {
	N = _N;
	REP(i, N - 1) {
		adj[U[i]].emplace_back(T[i], V[i]);
		adj[V[i]].emplace_back(T[i], U[i]);
	}
	REP(i, N) {
		W[i] = _W[i];
		sum_all += W[i];
	}
	dfs(0);
	sum = Fenwick(N);
	hld(0);
	REP(u, N) {
		sum.update(tin[u], W[u]);
		update(u, W[u]);
		t_res += W[u] * length[u];
	}
}

long long max_time(int u, int X) {
	int add = X - W[u];
	W[u] = X;
	sum_all += add;
	sum.update(tin[u], add);
	update(u, add);
	t_res += add * length[u];

	long long mid = sum_all / 2 + 1;
	u = pos[sum.lower_bound(mid)];
	if (sum.get(tin[u], tout[u]) < mid) {
		REPD(i, LOG) if (sum.get(tin[anc[u][i]], tout[anc[u][i]]) < mid) u = anc[u][i];
		u = anc[u][0];
	}
	return (t_res + (sum_all + 1) * length[u] - 2 * get(u)) * 2;
}

