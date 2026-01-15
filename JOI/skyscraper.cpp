#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int a[102];
ll dp[102][102][1002][3];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n, l;
	cin >> n >> l;
	if (n == 1) return cout << 1, 0;
	for (int i = 1; i <= n; i++) cin >> a[i];
	sort(a + 1, a + n + 1);
	a[n + 1] = 10000;
	dp[0][0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = 0; k <= l; k++) {
				for (int m = 0; m <= 2; m++) {
					int cost_diff = (2 * j - m) * (a[i + 1] - a[i]);
					if (cost_diff > k || i + j + 1 - m > n) continue;

					// Case 1
					dp[i][j][k][m] += dp[i - 1][j - 1][k - cost_diff][m];
					// Case 2
					if (m)
						dp[i][j][k][m] +=
						    (3 - m) * dp[i - 1][j - 1][k - cost_diff][m - 1];
					// Case 3
					dp[i][j][k][m] +=
					    (2 * j - m) * dp[i - 1][j][k - cost_diff][m];
					// Case 4
					if (m == 1)
						dp[i][j][k][m] +=
						    2 * j * dp[i - 1][j][k - cost_diff][m - 1];
					if (m == 2) {
						if (i == n)
							dp[i][j][k][m] +=
							    dp[i - 1][j][k - cost_diff][m - 1];
						else if (j > 1)
							dp[i][j][k][m] +=
							    (j - 1) * dp[i - 1][j][k - cost_diff][m - 1];
					}
					// Case 5
					if (m == 2) {
						if (i == n)
							dp[i][j][k][m] +=
							    dp[i - 1][j + 1][k - cost_diff][m];
						else
							dp[i][j][k][m] +=
							    j * (j - 1) *
							    dp[i - 1][j + 1][k - cost_diff][m];
					} else if (m == 1)
						dp[i][j][k][m] +=
						    j * j * dp[i - 1][j + 1][k - cost_diff][m];
					else
						dp[i][j][k][m] +=
						    j * (j + 1) * dp[i - 1][j + 1][k - cost_diff][m];

					dp[i][j][k][m] %= MOD;
				}
			}
		}
	}

	ll ans = 0;
	for (int i = 0; i <= l; i++) ans += dp[n][1][i][2];
	cout << ans % MOD;
	return 0;
}
