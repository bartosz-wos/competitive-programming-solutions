#include "bits/stdc++.h"
#define ll long long

using namespace std;

const int sz = 33;

char s[sz + sz];
char a[sz][sz];
int vi[sz][sz][2];
ll dp[sz][sz][2];
int n, m;

ll go(int i, int j, bool f) {
    if (i >= n || j >= m) return 0ll;
    if (f && a[i][j] > s[i + j]) return 0ll;
    if (n - 1 == i && m - 1 == j) return 1ll;
    if (a[i][j] < s[i + j]) f = 0;
    int& v = vi[i][j][f];
    ll& r = dp[i][j][f];
    if (v ++) return r;
    r += go(i + 1, j, f);
    r += go(i, j + 1, f);
    return r;
}

void zero() {
    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++)
            for (int k : {0, 1})
                dp[i][j][k] = vi[i][j][k] = 0;
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i ++)
        for (int j = 0; j < m; j ++)
            cin >> a[i][j];

    ll k;
    cin >> k;

    for (int i = 0; i < n + m; i ++)
        s[i] = 'z';
/*
    s[0] = 'a', s[1] = 'b', s[2] = 'f', s[3] = 'd', s[4] = 'g';

    cout << "init: " << go(0, 0, 1) << '\n';

    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++)
            cout << dp[i][j] << ' ';
        cout << '\n';
    }
*/
    for (int i = 0; i < n + m - 1; i ++) {
        char lo = 'a', hi = 'z';
        while (lo != hi) {
            char mi = (lo + hi) / 2;
            s[i] = mi;
            zero();
            //cout << i << ' ' << mi << ' ' << go(0, 0, 1) << ' ' << k << '\n';
            if (go(0, 0, 1) >= k)
                hi = mi;
            else lo = mi + 1;
        }
        s[i] = lo;
        //cout << "fn: " << i << ' ' << s[i] << '\n';
    }

    for (int i = 0; i < n + m - 1; i ++)
        cout << s[i];
    cout << '\n';
}

