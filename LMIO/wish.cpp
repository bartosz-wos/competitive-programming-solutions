#include <bits/stdc++.h>
using namespace std;

const long double maxd = 1e19;

long double sqrt128(__int128 x) {
	long double l = 0, r = maxd;
	for (int i=0; i<128; i++) {
		long double mid = (l + r) / 2;
		if (mid * mid <= x) {
			l = mid;
		} else {
			r = mid;
		}
	}
	return l;
}

void solve() {
	int n; long long r;
	cin >> n >> r;
	vector<long long> a(n), b(n), c(n), d(n);
	for (int i=0; i<n; i++) cin >> a[i] >> b[i] >> c[i] >> d[i];

	vector<pair<long long, bool>> evs;
	for (int i=0; i<n; i++) {
		__int128 dx = c[i] - a[i], dy = d[i] - b[i];
		__int128 A = dx * dx + dy * dy, B = 2 * (a[i] * dx + b[i] * dy), C = a[i] * a[i] + b[i] * b[i] - r * r;
		__int128 D = B * B - 4 * A * C;
		if (D >= 0) {
			long double sd = sqrt128(D);
			long double t1 = (-B + sd) / (2 * A);
			long double t2 = (-B - sd) / (2 * A);
			long long llt1 = ceil(min(t1, t2));
			long long llt2 = floor(max(t1, t2));
			if (llt1 <= llt2) {
				evs.emplace_back(llt1, 0);
				evs.emplace_back(llt2, 1);
			}
		}
	}

	sort(evs.begin(), evs.end());
	int ans = 0, cnt = 0;
	for (int i=0; i<(int)evs.size(); i++) {
		auto &[t, rem] = evs[i];

		if (t >= 0) ans = max(ans, cnt);

		if (rem) {
			cnt--;
		} else {
			cnt++;
		}
	}

	cout << ans << '\n';
}

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	int tcs = 1;
	while (tcs--) {
		solve();
	}
	return 0;
}
