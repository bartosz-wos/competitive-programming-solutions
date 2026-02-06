#include "bits/stdc++.h"
const signed MOD = 1e9 + 7;
const signed mod = 998244353;
using namespace std;
#define all(x) x.begin(), x.end()
#define ld long double
#define ll long long
#define pb push_back
#define mp make_pair
#define co cout <<
#define S second
#define F first
int a[105][20];
vector<int> v;
int n, m, k;
int ans;

int sol() {
    int f[m + 1] = {};
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < m) {
            bool flag = 1;
            for (int d : v) if (a[i][j] == d) flag = 0;
            if (flag) break;
            j++;
        }
        f[a[i][j]]++;
    }
    int mx = f[1], num = 1;

    for (int i = 2; i <= m; i++) {
        if (f[i] > mx) {
            mx = f[i];
            num = i;
        }
    }
    return num;
}

void rec(int i, int cn) {
    if (i == m) {
        if (sol() == k) ans = min(ans, cn);
        return;
    }
    v.pb(i + 1);
    rec(i + 1, cn + 1);
    v.pop_back();
    rec(i + 1, cn);
}

void solve() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    co sol() << endl;
    ans = m - 1;
    rec(0, 0);
    co ans;
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);
    signed t = 1;
    // cin >> t;
    while (t--) solve();
}
