#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n, T, ans = 0;
    cin >> n >> T;

    vector<ll> h(n), g(n); set<ll> s;
    for(int i=0; i<n; i++) cin >> h[i] >> g[i], s.insert(h[i]);
    vector<ll> comp(s.begin(), s.end());

    for(auto &x : h) x = lower_bound(comp.begin(), comp.end(), x) - comp.begin();

    auto meet = [&](int l, int r) {
        vector<array<ll, 3> > res;
        int len = r - l + 1;

        for(int s=1; s<(1<<len); s++) {
            ll sum = 0;
            int first = -1, last = -1, ok = 1;

            for(int i=0; i<len; i++) {
                if(s & (1 << i)) {
                    sum += g[l+i];
                    if(last > -1 && h[last] > h[l+i]) ok = 0;
                    if(first == -1) first = l + i;
                    last = l + i;
                }
            }

            if(ok) {
                if(sum >= T) ans++;
                res.push_back({ sum, first, last });
            }
        }

        return res;
    };

    vector<array<ll, 3> > L = meet(0, n/2-1);
    vector<array<ll, 3> > R = meet(n/2, n-1);
    sort(L.begin(), L.end());
    sort(R.rbegin(), R.rend());

    vector<ll> cnt(n);
    int p=-1;
    for(auto &[sum, _, rp] : L) {
        while(p + 1 < R.size() && sum + R[p+1][0] >= T) p++, cnt[h[R[p][1]]]++;
        for(int i=h[rp]; i<n; i++) ans += cnt[i];
    }

    cout << ans << '\n';
    return 0;
}
