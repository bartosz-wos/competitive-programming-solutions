#include <bits/stdc++.h>
#define int long long
using namespace std;

int n;

struct core{
    int c, f, v;
};

vector<core> a;

const int N = 1e5 + 5, INF = 1e18 + 5;
int dp[2][N];
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i++){
        int c, f, v; cin >> c >> f >> v;
        a.push_back({c, f, -v});
    }
    cin >> n;
    for(int i = 1; i <= n; i++){
        int c, f, v; cin >> c >> f >> v;
        a.push_back({-c, f, v});
    }

    sort(a.begin(), a.end(), [](core x, core y){return x.f > y.f || (x.f == y.f && x.c > y.c);});
    for(int i = 1; i < N; i++) dp[0][i] = dp[1][i] = -INF;
    dp[0][0] = 0;
    int cnt = 0;
    for(int i = 0; i < (int) a.size(); i++){
        for(int j = cnt; j >= max(-a[i].c, 0LL); j--){
            if(dp[0][j] == -INF) continue;
            dp[1][j + a[i].c] = max(dp[1][j + a[i].c], dp[0][j] + a[i].v);
        }
        if(a[i].c > 0) cnt += a[i].c;
        for(int j = 0; j <= cnt; j++){
            dp[0][j] = dp[1][j];
        }
    }
    int ans = 0;
    for(int i = 0; i < N; i++){
        ans = max(ans, dp[0][i]);
    }
    cout << ans << '\n';
    return 0;
}


