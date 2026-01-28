#include <bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 1e5+5;
const int MOD = 1e9+7;
int dp[MAXN],ad[MAXN][317];
signed main()
{
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int N; cin >> N;
    int B = sqrt(N);
    dp[1] = 1; int ans = 0;
    for(int i = 1;i<=N;++i){
        int d,x; cin >> d >> x;
        for(int j = 1;j<=B;++j){
            if(i+j <= N) ad[i+j][j] = (ad[i+j][j]+ad[i][j])%MOD;
            dp[i] = (dp[i]+ad[i][j])%MOD;
        }
        ans = (ans+dp[i])%MOD;
        if(d == 0) continue;
        if(d > B){
            int maxx = min(N,i+x*d);
            for(int j = i+d;j<=maxx;j += d){
                dp[j] = (dp[j]+dp[i])%MOD;
            }
        }
        else{
            ad[i+d][d] = (ad[i+d][d]+dp[i])%MOD;
            if(i+d*(x+1) <= N) ad[i+d*(x+1)][d] = (ad[i+d*(x+1)][d]-dp[i]+MOD)%MOD;
        }
    }
    cout << ans << "\n";
    return 0;
}

