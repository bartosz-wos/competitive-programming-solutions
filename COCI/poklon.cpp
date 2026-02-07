#include <bits/stdc++.h>

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
//#define int long long

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int mod = 1e9 + 7;
const int LOG = 20;
const int maxn = 1e5 + 5;

struct BIT {
    int n;
    vector<int> tree, val;

    BIT(int _n) : n(_n+10), tree(_n+60), val(_n+60) {}

    void update(int p, int v) {
        val[p] += v;
        for(p++; p<n; p+=p&-p) tree[p] += v;
    }

    ll query(int p) {
        ll ans = 0;
        for(p++; p>0; p-=p&-p) ans += tree[p];
        return ans;
    }

    ll query(int l, int r) { return query(r) - query(l-1); }
    void set(int p, int v) { update(p, v - val[p]); }
};


signed main() {
    ios_base::sync_with_stdio(false);
    cout.tie(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for(int &x : v) cin >> x;

    vector<pii> qus[n];
    for(int i=0; i<q; i++) {
        int l, r;
        cin >> l >> r;
        qus[r-1].push_back({ l-1, i });
    }

    vector<int> ans(q);
    map<int, vector<int> > mp;
    BIT bit(n);

    for(int i=0; i<n; i++) {
        mp[v[i]].push_back(i);
        int sz = mp[v[i]].size();
        if(sz >= 2) bit.set(mp[v[i]][sz-2], 1);
        if(sz >= 3) bit.set(mp[v[i]][sz-3], -1);
        if(sz >= 4) bit.set(mp[v[i]][sz-4], 0);
        for(auto &[l, id] : qus[i]) ans[id] = bit.query(l, i); 
    }

    for(int &x : ans) cout << x << '\n';
    return 0;
}
