#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fi first
#define se second
#define rep(i, a, b) for (auto i = a; i <= b; ++i)
#define per(i, b, a) for (auto i = b; i >= a; --i)
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()
#define lsb(x) (x)&(-x)

void setIO(string name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);cout.tie(nullptr);
    if (!name.empty()) {
        freopen((name + ".in").c_str(), "r", stdin);
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

ll fexp(ll a, ll b, ll m) {
    ll p = a;
    ll ans = 1;

    while (b > 0) {
        if (b % 2 != 0) ans = (ans*p)%m;
        p = (p*p)%m;
        b >>= 1;
    }
    return ans;
}

const int MAXN = 2e5 + 10;
const int INF = 1e18 + 5;
const int MOD = 1e9 + 7;

typedef long double dl;

void solve() {
    int n,l;
    cin >> n >> l;
    vector<pii> pos(n);
    for (auto &[x,y] : pos)cin >> x >> y;

    dl lo = 1, hi = 1.5e9;
    while ((hi-lo)>1e-4) {
        dl mid = (lo + hi) / 2;
        dl cr=0;

        for (const auto &[xi,yi] : pos) {
            if (mid*mid < yi*yi) continue;
            dl sq = sqrt((dl)mid*mid - (dl)yi*yi);
            dl li = xi - sq, ri = xi + sq;
            if (li <= cr) cr = max(ri,cr);
        }
        if (cr >= l) hi = mid;
        else lo = mid;
    }
    cout << fixed << setprecision(4) << hi << '\n';
}

int32_t main() {
    setIO();
    int tt = 1;
    //cin >> tt;

    while (tt-- > 0) solve();
}
