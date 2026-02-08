#include "bits/stdc++.h"
using namespace std;

#define s second
#define f first
#define pb push_back

typedef long long ll;
#define int long long

typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef vector<int> vi;

#define FOR(i, a, b) for (int i = (a); i<b; i++)

bool ckmin(int& a, int b){ return b < a ? a = b, true : false; }

bool ckmax(int& a, int b){ return b > a ? a = b, true : false; }

const int INF = 2e18;

struct Line {
	int m, b;
	int evalX(int x) {
		return m * x + b;
	}
	double isectX(Line l) {
		return ((double) l.b - (double) b) / ((double) m - (double) l.m);
	}
};

deque<Line> line;
void add(Line l) {
	while (line.size() > 0 && line[0].m == l.m) {
		if (l.b < line[0].b) line.pop_front();
		else return;
	}
	while (line.size() > 1 && line[0].isectX(line[1]) < l.isectX(line[1])) line.pop_front();
	line.push_front(l);

}

int query(int pos) {

	int lo = 0;
	int hi = line.size() - 1;

	while (lo < hi) {
		int m = (lo + hi) / 2;
		if (line[m].isectX(line[m + 1]) > (double) pos) hi = m;
		else lo = m + 1;
	}

	// for (auto val: line) best = min(best, val.evalX(pos));
	return min(0ll, line[lo].evalX(pos));
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int x, n, m, w, t;
	cin >> x >> n >> m >> w >> t;
	m++;

	vector<array<int, 3> > all(n + m + 1, {-1, -1, 1});

	FOR(i, 1, n + 1) {
		cin >> all[i][1];
		all[i][0] = all[i][1] % t;
		all[i][2] = 0;
	}	
	FOR(i, n + 1, n + m) cin >> all[i][0] >> all[i][1];	
	all[n + m] = {x % t, x, 0};


	sort(all.begin(), all.end());

	vi prefc(n + m + 1, 0);
	vi cnt(n + m + 1, 0);
	for (int i = 1; i <= n + m; i++) {
		prefc[i] = prefc[i-1] + all[i][1] * all[i][2];
		cnt[i] = cnt[i-1] + all[i][2];
	}
	vi dp(n + m + 1, 0);
	int periods = (x / t);

	// add({0, 0});

	for (int i = 1; i <= n + m; i++) {
		// cout << all[i][0] << ' ' << all[i][1] << ' ' << all[i][2] << endl;
		if (all[i][2] == 0) { // refill point
			int skip = (all[i][1] - all[i][0]) / t;
			dp[i] = min(dp[i-1], query(-skip * w) + prefc[i] + skip * w * cnt[i]);
			// ckmin(dp[i], 0);
			// for (int j = 0; j < i; j++) {
			// 	int skip = (all[i][1] - all[i][0]) / t;
			// 	ckmin(dp[i], prefc[i] + skip * w * cnt[i] - skip * w * cnt[j] - prefc[j] + dp[j]);
			// }
		} else {
			dp[i] = dp[i-1] + w * (periods + (all[i][0] <= (x % t)));
		}

		add({cnt[i], -prefc[i] + dp[i]});


	}

	cout << dp[n + m] + (periods + 1ll) * w << endl;
}
