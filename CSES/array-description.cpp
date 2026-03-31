#include<iostream>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
constexpr int mod = 1e9+7;
 
int n, m, tab[100007], dp[100007][107], ans;
int main() {
	ios;
	cin >> n >> m;
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
 
	if(tab[0])
		dp[0][tab[0]] = 1;
	else
		for(int i = 1; i <= m; ++i)
			dp[0][i] = 1;
 
	for(int i = 1; i < n; ++i) {
		if(!tab[i]) {
			for(int j = 1; j <= m; ++j) {
				if(j >= 2)
					dp[i][j] = (dp[i][j] + dp[i-1][j-1]) % mod;
				dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;
				if(j < m)
					dp[i][j] = (dp[i][j] + dp[i-1][j+1]) % mod;
			}
		}
		else {
			if(tab[i] >= 2)
				dp[i][tab[i]] = (dp[i][tab[i]] + dp[i-1][tab[i]-1]) % mod;
			dp[i][tab[i]] = (dp[i][tab[i]] + dp[i-1][tab[i]]) % mod;
			if(tab[i] < m)
				dp[i][tab[i]] = (dp[i][tab[i]] + dp[i-1][tab[i]+1]) % mod;
		}
	}
	for(int i = 1; i <= m; ++i)
		ans = (ans + dp[n-1][i]) % mod;
	cout << ans;
}
