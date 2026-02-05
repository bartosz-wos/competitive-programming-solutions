#include <bits/stdc++.h>
#define N 1000005
#define int long long
using namespace std;
const int mod = 1e9 + 7;
int n, m, dr[N], dc[N], q, ans, x, sum, tmp, base;
char c;
int32_t main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> n >> m >> q;
	for (int i = 0; i <= max(n, m); ++i) dr[i] = dc[i] = 1;
	while (q--) {
		cin >> c >> x >> tmp;
		if (c == 'S') dc[x] = (dc[x] * tmp) % mod;
		else dr[x - 1] = (dr[x - 1] * tmp) % mod;
	}
	for (int i = 0; i < n; ++i) {
		sum = (sum + dr[i]) % mod;
		base = (base + (((i * m) % mod) * dr[i]) % mod) % mod;
	}
	sum %= mod;
	base %= mod;
	for (int i = 1; i <= m; ++i) ans = (ans + (((base + (i * sum) % mod) * dc[i]) % mod)) % mod;
	cout << ans % mod << "\n";
	return 0;
}
