#include <iostream>
using namespace std;
constexpr int MOD = 1000000007;
 
 
int dp[1000007];
int main() {
    dp[0] = 0;
    dp[1] = 2;
 
    for(int i = 2; i <= 1000000; ++i)
        dp[i] = (dp[i-1] << 1) % MOD;
 
    int n;
    cin >> n;
 
    cout << dp[n];

