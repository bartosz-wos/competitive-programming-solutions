#include<bits/stdc++.h>
using namespace std;
int n, a, b;
double dp[601][101];
 
int main() {
        ios::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
        cin >> n >> a >> b;
        dp[0][0] = 1.0;
        for(int j = 1; j <= n; ++j)
                for(int i = 1; i <= 600; ++i)
                        for(int k = 1; k <= 6; ++k)
                                if(i - k >= 0)
                                        dp[i][j] += dp[i-k][j-1] * (1.0 / 6.0);
 
        double ans = 0;
        for(int i = a; i <= b; ++i)
                ans += dp[i][n];
        cout << setprecision(6) << fixed << ans;
}
