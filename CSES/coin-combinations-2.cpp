#include<bits/stdc++.h>
using namespace std;
constexpr int mod = 1e9+7;
int n, x, c[101];
long long dp[1000001];
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> x;
	dp[0] = 1;
	for(int i = 0; i < n; ++i)
		cin >> c[i];
	sort(c, c + n);
 
	for(int i = 0; i < n; ++i)
		for(int j = 0; j <= x; ++j)
			if(j - c[i] >= 0)
				dp[j] = (dp[j] + dp[j-c[i]]) % mod;
 
	cout <<dp[x];
}
