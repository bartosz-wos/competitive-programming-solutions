#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int maxn = 507;
constexpr int inf = 2e9;
int dp[maxn][maxn], a, b;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> a >> b;
    for(int i = 1; i <= a; ++i)
        for(int j = 1; j <= b; ++j)
            dp[i][j] = inf;
    for(int i = 0; i < maxn; ++i)
        dp[i][i] = 0;
 
    for(int i = 1; i <= a; ++i)
        for(int j = 1; j <= b; ++j) {
            for(int cut = 1; cut < i; ++cut)
                dp[i][j] = min(dp[i][j], dp[cut][j] + dp[i-cut][j] + 1);
            for(int cut = 1; cut < j; ++cut)
                dp[i][j] = min(dp[i][j], dp[i][cut] + dp[i][j-cut] + 1);
        }
    cout << dp[a][b];
}
