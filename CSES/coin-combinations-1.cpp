#include<iostream>
using namespace std;
constexpr int mod = 1000000007;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
int k, n, dp[1000007], coins[107];
int main() {
	ios;
	dp[0] = 1;
	cin >> k >> n;
	for (int i = 0; i < k; ++i)
		cin >> coins[i];
 
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < k; ++j)
			if (i - coins[j] >= 0)
				dp[i] = (dp[i] + dp[i - coins[j]]) % mod;
 
	cout << dp[n];
}
