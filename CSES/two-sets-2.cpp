#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9+7;
int n;
ll dp[501][127500];
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    dp[0][0] = 1;
    cin >> n;
    int t = ( n * (n+1) ) >> 1;
    if(t & 1)
        cout << 0, exit(0);
    t >>= 1;
    for(int i = 1; i < n; ++i)
        for(int j = 0; j <= t; ++j) {
            dp[i][j] = dp[i-1][j];
            if(j - i >= 0)
                dp[i][j] = (dp[i][j] + dp[i-1][j-i]) % mod;
        }
    cout << dp[n-1][t];
}
