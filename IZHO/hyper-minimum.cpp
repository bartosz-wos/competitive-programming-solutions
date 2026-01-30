#include <bits/stdc++.h>
/**
#pragma GCC optimize ("O3")
#pragma GCC optimize ("fast-math")
#pragma GCC optimize ("unroll-loops")
**/
using namespace std;
//#define int long long
#define ll long long
#define all (x) begin(x), end (x)
#define xx first
#define yy second
#define f(i, n) for (int i = 0; i < n; ++ i)
using pii = pair <int, int>;
using tii = tuple <int, int, int>;


int dp[35][35][35][35];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    f(i, n) f(i1, n) f(i2, n) f(i3, n) cin >> dp[i][i1][i2][i3];
	f(i, n) f(i1, n) f(i2, n) f(i3, n - m + 1) f(X, m) dp[i][i1][i2][i3] = min(dp[i][i1][i2][i3], dp[i][i1][i2][i3 + X]);
	f(i, n) f(i1, n) f(i2, n - m + 1) f(i3, n) f(X, m) dp[i][i1][i2][i3] = min(dp[i][i1][i2][i3], dp[i][i1][i2 + X][i3]);
	f(i, n) f(i1, n - m + 1) f(i2, n) f(i3, n) f(X, m) dp[i][i1][i2][i3] = min(dp[i][i1][i2][i3], dp[i][i1 + X][i2][i3]);
	f(i, n - m + 1) f(i1, n) f(i2, n) f(i3, n) f(X, m) dp[i][i1][i2][i3] = min(dp[i][i1][i2][i3], dp[i + X][i1][i2][i3]);
	f(i, n - m + 1) f(i1, n - m + 1) f(i2, n - m + 1) f(i3, n - m + 1) cout << dp[i][i1][i2][i3] << ' ';
	cout << '\n';
    return 0 ^ 0;
}
