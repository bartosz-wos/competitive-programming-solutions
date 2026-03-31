#include <iostream>
using namespace std;
constexpr int INF = 1000000000;
 
int n, w, c[1001], dp[1000007];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> w;
 
	for(int i = 1; i <= n; ++i) cin >> c[i];
	for(int i = 1; i <= w; ++i) dp[i] = INF;
 
	for(int i = 1; i <= w; ++i)
		for(int j = 1; j <= n; ++j)
			if(i - c[j] >= 0)
				dp[i] = min(dp[ i - c[j] ] + 1, dp[i]);
 
		if(dp[w] == INF) dp[w] = -1;
 
		cout << dp[w];
 
}
