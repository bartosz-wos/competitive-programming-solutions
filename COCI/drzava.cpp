#include <bits/stdc++.h>
using namespace std;
 
#define fast ios::sync_with_stdio(0);cin.tie(0);
#define s second
#define f first
typedef long long ll;
const ll MOD = 998244353;
const ll LOGN = 20; 
const ll MAXN = 5e4 + 101;

struct P {
	double x, y;
	ll k;
	void read() {
		cin >> x >> y >> k;
	}
	P() { }
	P(double _x, double _y, ll _k) : x(_x), y(_y), k(_k) { }
};

vector<P> v;
set<pair<double,int>> s;
int par[MAXN], sz[MAXN], N, K;
int find(int node) {
	if (node == par[node])
		return node;
	return par[node] = find(par[node]);
}

void unite(int a, int b) {
	a = find(a);
	b = find(b);
	if (a == b)
		return ; 
	if (sz[b] > sz[a])
		swap(a, b);
	par[b] = a;
	sz[a] += sz[b];
}

int dp[MAXN][31];
ll dist(int a, int b) {
	ll dx = v[a].x - v[b].x;
	ll dy = v[a].y - v[b].y;
	return dx * dx + dy * dy;
}

bool check(double d) {
	memset(dp, 0, sizeof(dp));
	s.clear(); 
	for (int i = 0; i < MAXN; i++)
		par[i] = i, sz[i] = 1;

	int l = 0, r = 0;
	for (r = 0; r < N; r++) {
		int R = r;
		while (l < N && v[r].x - v[l].x > d) {
			s.erase({v[l].y, l});
			l++;
		}
		while (R < N && v[r].x == v[R].x) {
			s.insert({v[R].y, R});

			auto it = s.lower_bound({v[R].y - d, -1});
			for ( ; it != s.end() && (*it).f <= v[R].y + d; it++) {
				if (dist(R, (*it).s) <= d * d)
					unite(R, (*it).s);
				if (sz[find(R)] >= K)
					return true;
			}
			R++;
		}
		r = R - 1;
	}

	for (int i = 0; i < N; i++) {
		int p = find(i);
		int new_dp[31];
		for (int j = 0; j < 31; j++)
			new_dp[j] = dp[p][j];
		for (int j = K-1; j >= 0; j--) {
			if (dp[p][j])
				new_dp[(j + v[i].k) % K] = true;
		}
		for (int j = 0; j < 31; j++)
			dp[p][j] = new_dp[j];
		dp[p][v[i].k] = true;
	}

	for (int i = 0; i < N; i++) {
		if (dp[find(i)][0])
			return true;
	}
	return false;
}

int main() {
	fast
	cin >> N >> K;

	v = vector<P>(N);
	for (int i = 0; i < N; i++) {
		v[i].read();
		v[i].k %= K;
	}
	sort(v.begin(), v.end(), [&](P A, P B) {
		return make_pair(A.x, A.y) < make_pair(B.x, B.y);
	});

	double L = 0.0, R = 200000000.0;
	double ans = -1.0;
	while (R - L > 0.000001) {
		double mid = L + (R-L) / 2;
		if (check(mid)) {
			R = mid;
			ans = mid;
		} else
			L = mid;
	}
	cout << setprecision(3) << fixed << ans << "\n";
}
