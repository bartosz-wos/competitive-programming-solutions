#include<bits/stdc++.h>
using namespace std;

void fast() {
    std::ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
}


#define sz(x) (int)x.size()

int dp[20][1ll << 20], a[20], b[20], n, m, p[21];

int mem(int mask, int j) {
    if (j == n){
        return 1;
    }
    int rem = m - __builtin_popcount(mask);
    if (rem < n - j)return 0;
    int &ret = dp[j][mask];
    if (~ret)return ret;
    ret = 0;
    int curs = 0;
    for(int i = 0; i < m; i++) {
        if (mask >> i & 1){
            curs += b[i];
        }
    }
    curs -= p[j];
    for(int i = 0; i < m; i++) {
        if (mask >> i & 1)continue;
        if (curs + b[i] < a[j]) {
            ret |= mem(mask | (1ll << i), j);
        }
        else if (curs + b[i] == a[j]) {
            ret |= mem(mask | (1ll << i), j + 1);
        }
    }
    return ret;
}

void burn(){
    cin >> n >> m;
    for(int i = 0; i < n; i++)cin >> a[i], p[i + 1] = a[i] + p[i];
    for(int j = 0; j < m; j++)cin >> b[j];
    memset(dp, -1, sizeof dp);
    cout << (mem(0, 0)?"YES\n":"NO\n");
}

int32_t main() {
    fast();
    int t = 1;
    //cin >> t;
    while(t--) {
        burn();
    }
}
