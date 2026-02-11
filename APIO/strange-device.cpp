#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define i64 long long
#define i128 __int128_t
#define isz(x) (int)x.size()
using namespace std;

void solve() {
    int n; 
    i64 A, B;
    cin >> n >> A >> B;
    
    i64 g = __gcd(A, B + 1);
    auto coef = A / g;
    i128 mod = i128(1) * coef * B;

    map<i128, int> mp;
    function<void(i128, i128)> add = [&](i128 l, i128 r) -> void {
        if (l > r) {
            add(l, mod - 1);
            add(0, r);
        }
        else {
            mp[l]++, mp[r + 1]--;
        }
    };

    for (int i = 0; i < n; ++i) {
        i64 l, r;
        cin >> l >> r;
        
        if (r - l + 1 >= mod) {
            cout << (i64)mod << endl;
            return;
        }

        l = l % mod, r = r % mod;
        add(l, r);
    }

    i64 res = 0;
    i128 prv = 0, cur = 0;
    for (auto [val, cnt] : mp) {
        if (cur) res += val - prv;
        cur += cnt, prv = val;
    }
    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while(t--) 
	    solve();
}

