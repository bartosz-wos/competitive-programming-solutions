#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr int mod = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    for (; t > 0; --t) {
        int n, k; cin >> n >> k;
        vector<ll> e(n + 1);
        e[0] = 1;
        for (int i = 1; i <= n; ++i) {
            e[i] = e[i - 1] * k % mod;
        }
        vector<ll> dp(k + 1, 1);
        dp[1] = 0;
        ll ans = e[n - 1];
        for (int i = 2; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                for (int l = j + j; l <= k; l += j) {
                    dp[j] = (dp[j] + dp[l]) % mod;
                }
            }
            for (int j = k; j > 0; --j) {
                dp[j] = (dp[j] + dp[0]) * (k / j) % mod;
                for (int l = j + j; l <= k; l += j) {
                    dp[j] = (dp[j] - dp[l] + mod) % mod;
                }
            }
            ans = (ans + dp[1] * e[n - i] % mod) % mod;
            dp[0] = dp[1];
            dp[1] = 0;
        }
        cout << ans << "\n";
    }
}


