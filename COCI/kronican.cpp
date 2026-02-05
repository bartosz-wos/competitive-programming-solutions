#include <bits/stdc++.h>
using namespace std;

const int nx=20;

int n, k, c[nx][nx], dp[(1<<nx)], res=INT_MAX;

int main()
{
    cin.tie(NULL)->sync_with_stdio(false);
    cin>>n>>k;
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) cin>>c[i][j];
    if (n==k) return cout<<0, 0;
    for (int msk=(1<<n)-2; msk>=0; msk--)
    {
        dp[msk]=1e9;
        if (__builtin_popcount(msk)<k) continue;
        for (int i=0; i<n; i++) 
        {
            if (!(msk&(1<<i))) 
            {
                int mn=1e9;
                for (int j=0; j<n; j++) if (msk&(1<<j)) mn=min(mn, c[i][j]);
                dp[msk]=min(dp[msk], dp[msk|(1<<i)]+mn);
            }
        }
        if (__builtin_popcount(msk)==k) res=min(res, dp[msk]);
    }
    cout<<res;
}
