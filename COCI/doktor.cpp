#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
#define all(x) (x).begin(), (x).end()

const int MAXN = 5E5 + 5;

vector <int> vall[2 * MAXN];

#define ONLINE_JUDGE
void solve() {
    int n;
    cin >> n;

    vector <int> v(n +1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    vector <int> pref(n +2), suf(n +2);
    for(int i = 1; i <= n; i++) {
        pref[i] = pref[i -1] + (v[i] == i);
    }

    for(int i = n; i >= 1; i--) {
        suf[i] = suf[i +1] + (v[i] == i);
    }

    vector <int> c(n +1);
    for(int i = 1; i <= n; i++) {
        c[i] = v[i] + i;
        vall[c[i]].emplace_back(i);
        //cerr << c[i] << " \n"[i == n];
    }

    array <int, 3> ans = {-1, 0, 0};
    for(int i = 1; i <= n; i++) {
        int l = min(i, v[i]), r = max(i, v[i]);
        auto it1 = lower_bound(all(vall[i + v[i]]), l);
        auto it2 = lower_bound(all(vall[i + v[i]]), r +1);
        int calc = pref[l -1] + (it2 - it1) + suf[r +1];

        if(calc > ans[0]) {
            ans = {calc, v[l], v[r]};
        }
    }

    cout << ans[1] << " " << ans[2];

    return;
}

signed main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t = 1; //cin >> t;
    for(int i = 1; i <= t; i++) {
        solve();
    }

    return 0;
}
