#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
int t, n;
ll dp[1000001][3];
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	dp[1][1] = 1;
	dp[1][2] = 1;
 
	for(int i = 2; i <= 1e6; ++i) {
		dp[i][1] = ( dp[i-1][1] * 4 % mod + dp[i-1][2] ) % mod;
		dp[i][2] = ( dp[i-1][1] + dp[i-1][2] * 2 % mod ) % mod;
	}
 
	cin >> t;
	while(t--) {
		cin >> n;
		cout << (dp[n][1] + dp[n][2]) % mod << '\n';
	}
}
