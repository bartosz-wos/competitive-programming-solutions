#include<bits/stdc++.h>
using namespace std;
int n, x, pages[1001], price[1001], dp[2][100001];
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> x;
	for(int i = 0; i < n; ++i)
		cin >> price[i];
	for(int i = 0; i < n; ++i)
		cin >> pages[i];
 
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= x; ++j) {
			if(!i or !j)
				dp[i&1][j] = 0;
			else if(j - price[i-1] >= 0)
				dp[i&1][j] = max(dp[(i-1)&1][j], dp[(i-1)&1][j-price[i-1]] + pages[i-1]);
			else
				dp[i&1][j] = dp[(i-1)&1][j];
		}
	cout << dp[n&1][x];
}
