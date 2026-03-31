#include<bits/stdc++.h>
using namespace std;
constexpr int mod = 1e9+7;
int n, dp[1007][1007];
char p;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n;
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            cin >> p;
            if(p == '*') continue;
            else if(i == 1 and j == 1)
                dp[1][1] = 1;
            else
                dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % mod;
        }
    cout << dp[n][n];
}
