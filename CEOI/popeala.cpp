#include <bits/stdc++.h>
#define ii pair<int, int>
#define fi first
#define se second
#define inf 0x3f3f3f3f3f3f3f3f
using namespace std;
using ll = long long;
const ll mod=1e9+7;
const int nx=2e4+5;
int n, t, s, last[nx][55];
ll a[nx], dp[55][nx], tmp[55];
char c[55][nx];
int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>t>>s;
    for(int i = 1; i <= t; i++)
        cin>>a[i], a[i]+=a[i-1];
    for(int i = 0; i < n; i++)
    {
        for(int j = 1; j <= t; j++)
        {
            cin>>c[i][j];
            last[j][i]=(c[i][j]=='1')?last[j-1][i]:j;
        }
    }
    for(int i = 1; i <= t; i++)
    {
        last[i][n]=i;
        sort(last[i], last[i]+n+1);
    }
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0]=0;
    for(int i = 1; i <= s; i++)
    {
        for(int j = 0; j <= n; j++)
            tmp[j]=inf;
        for(int j = 1; j <= t; j++)
        {
            for(int k = 0; k <= n; k++)
            {
                for(int p = last[j-1][k]; p < last[j][k]; p++)
                    tmp[k]=min(tmp[k], dp[i-1][p]-1ll*a[p]*k);
                dp[i][j]=min(dp[i][j], tmp[k]+1ll*a[j]*k);
            }
        }
        cout<<dp[i][t]<<'\n';
    }
}
