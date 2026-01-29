#include<bits/stdc++.h>
#define mod 1000000007
using namespace std;

typedef long long ll;

int n, a, b;
inline int add(int a, int b)
{
    if(!b)
        return a;
    int x = a+b;
    if(x >= mod)
        x -= mod;
    else
        if(x < 0)
            x += mod;
    return x;
}
ll mul(ll a, ll b)
{
    return (a * b) % mod;
}
ll dp[2002][2002];
int main()
{
    cin >> n >> a >> b;
    dp[1][1] = 1;
    for(int i = 2; i <= n; ++i)
        for(int j = 1; j <= n; ++j)
        {
            if(i == a || i == b)
                dp[i][j] = add(dp[i-1][j-1], dp[i-1][j]);
            else
                dp[i][j] = add(mul(dp[i-1][j+1], j), mul(dp[i-1][j-1], j - (i > a) - (i > b)));
        }
    cout << dp[n][1];
    return 0;
}
