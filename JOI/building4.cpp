#include <bits/stdc++.h>
using namespace std;
#define rMax(x, y) x = max(x, y)
#define rMin(x, y) x = min(x, y)
 
const int LIM = 1e6+1;
 
int n, a[2][LIM];
array<int, 2> dp[2][LIM];
 
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> n; n *= 2;
	for(int j : {1, 0})
		for(int i=1; i<=n; ++i) cin >> a[j][i];
 
	for(int i=1; i<=n; ++i){
		for(int j : {0, 1}){
			dp[j][i] = {n+1, -1};
			for(int k : {0, 1})
				if(a[j][i] >= a[k][i-1])
					rMin(dp[j][i][0], dp[k][i-1][0]+j),
					rMax(dp[j][i][1], dp[k][i-1][1]+j);
		}
	}
 
	int u = -1, j = 0;
 
	for(int k : {0, 1})
		if(dp[k][n][0] <= n/2 && n/2 <= dp[k][n][1]) u = n, j = k;
 
	if(u < 0){
		cout << -1;
	}else{
		string ans(n, ' ');
		int c = n/2;
		while(u--){
			ans[u] = 'B'-j;
			c -= j;
			j = a[j][u+1] >= a[1][u] && dp[1][u][0] <= c && c <= dp[1][u][1];
		}
		cout << ans;
	}
}
