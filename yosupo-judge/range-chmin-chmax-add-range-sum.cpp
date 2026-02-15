#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vl vector<ll>
#define ov3(a, b, c, name, ...) name
#define rep0(n) for(ll aaaaa = 0; aaaaa < n; ++aaaaa)
#define rep1(i, n) for(ll i = 0; i < (n); i++)
#define rep2(i, a, b) for(ll i = (a); i < (b); i++)
#define rep(...) ov3(__VA_ARGS__, rep2, rep1, rep0)(__VA_ARGS__)
#define per(i, a, b) for(ll i = (a) - 1; i >= (b); i--)
#define all(a) begin(a), end(a)
#define si(a) (int)(size(a))
#define lb(v, x) (lower_bound(all(v), x) - begin(v))
#define eb emplace_back
bool chmin(auto &a, auto b) { return a > b ? a = b, 1 : 0; }
bool chmax(auto &a, auto b) { return a < b ? a = b, 1 : 0; }

const int INF = 1e9 + 100;
const ll INFL = 3e18 + 100;

#define i128 __int128_t

struct _ {
    _() { cin.tie(0)->sync_with_stdio(0), cout.tie(0); }
} __;

struct Segtree_beats {
    ll op(int type, ll x, ll y) { return type ? min(x, y) : max(x, y); }
    bool cmp(int type, ll x, ll y) { return type ? x < y : x > y; }
    struct alignas(32) Node {
        ll sum = 0;
        ll a1[2] = {}, a2[2] = {-INFL, INFL}, ac[2] = {1, 1}, add = 0;
    };

    vector<Node> v;
    ll n, log, e[3] = {-INFL, INFL, 0};

    Segtree_beats() {}
    Segtree_beats(int n) : Segtree_beats(vl(n)) {}
    Segtree_beats(const vl &a) {
        n = 1, log = 0;
        while(n < si(a)) n <<= 1, log++;
        v.resize(2 * n);
        rep(i, si(a)) { v[i + n].sum = v[i + n].a1[0] = v[i + n].a1[1] = a[i]; }
        per(i, n, 1) update(i);
    }

    void add(int l, int r, ll x) { inner_apply<0>(l, r, x); }
    void chmin(int l, int r, ll x) { inner_apply<1>(l, r, x); }
    void chmax(int l, int r, ll x) { inner_apply<2>(l, r, x); }
    void update(int l, int r, ll x) { inner_apply<3>(l, r, x); }
    ll prod_max(int l, int r) { return inner_fold<0>(l, r); }
    ll prod_min(int l, int r) { return inner_fold<1>(l, r); }
    ll prod_sum(int l, int r) { return inner_fold<2>(l, r); }

  private:
    void update(int k) {
        Node &p = v[k];
        Node &l = v[k * 2 + 0];
        Node &r = v[k * 2 + 1];
        p.sum = l.sum + r.sum;
        rep(t, 2) {
            if(l.a1[t] == r.a1[t]) {
                p.a1[t] = l.a1[t];
                p.a2[t] = op(t, l.a2[t], r.a2[t]);
                p.ac[t] = l.ac[t] + r.ac[t];
            } else {
                bool f = cmp(t, l.a1[t], r.a1[t]);
                p.a1[t] = f ? l.a1[t] : r.a1[t];
                p.ac[t] = f ? l.ac[t] : r.ac[t];
                p.a2[t] = op(t, f ? r.a1[t] : l.a1[t], f ? l.a2[t] : r.a2[t]);
            }
        }
    }

    void push_add(int k, ll x) {
        Node &p = v[k];
        p.sum += x << (log + __builtin_clz(k) - 31);
        rep(t, 2) {
            p.a1[t] += x;
            if(p.a2[t] != e[t]) p.a2[t] += x;
        }
        p.add += x;
    }

    void push(int cmd, int k, ll x) {
        Node &p = v[k];
        p.sum += (x - p.a1[cmd]) * p.ac[cmd];
        if(p.a1[cmd ^ 1] == p.a1[cmd]) p.a1[cmd ^ 1] = x;
        if(p.a2[cmd ^ 1] == p.a1[cmd]) p.a2[cmd ^ 1] = x;
        p.a1[cmd] = x;
    }
    void push(int k) {
        Node &p = v[k];
        if(p.add) {
            rep(t, 2) push_add(k * 2 + t, p.add);
            p.add = 0;
        }
        rep(t, 2) rep(s, 2) if(cmp(t, v[k * 2 + s].a1[t], p.a1[t])) push(t, k * 2 + s, p.a1[t]);
    }

    void subtree_ch(int cmd, int k, ll x) {
        if(!cmp(cmd, v[k].a1[cmd], x)) return;
        if(cmp(cmd, x, v[k].a2[cmd])) { return push(cmd, k, x); }
        push(k);
        rep(t, 2) subtree_ch(cmd, k * 2 + t, x);
        update(k);
    }

    template <int cmd> inline void _apply(int k, ll x) {
        rep(i, 2) if(cmd >> i & 1) subtree_ch(i, k, x);
        if constexpr(cmd == 0) push_add(k, x);
    }

    template <int cmd> void inner_apply(int l, int r, ll x) {
        if(l == r) return;
        l += n, r += n;
        per(i, log + 1, 1) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while(l < r) {
                if(l & 1) _apply<cmd>(l++, x);
                if(r & 1) _apply<cmd>(--r, x);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        rep(i, 1, log + 1) {
            if(((l >> i) << i) != l) update(l >> i);
            if(((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <int cmd> inline void op(ll &a, const Node &b) {
        if constexpr(cmd <= 1) a = op(cmd, a, b.a1[cmd]);
        if constexpr(cmd == 2) a += b.sum;
    }

    template <int cmd> ll inner_fold(int l, int r) {
        if(l == r) return e[cmd];
        l += n, r += n;
        per(i, log + 1, 1) {
            if(((l >> i) << i) != l) push(l >> i);
            if(((r >> i) << i) != r) push((r - 1) >> i);
        }
        ll lx = e[cmd], rx = e[cmd];
        while(l < r) {
            if(l & 1) op<cmd>(lx, v[l++]);
            if(r & 1) op<cmd>(rx, v[--r]);
            l >>= 1;
            r >>= 1;
        }
        if constexpr(cmd <= 1) lx = op(cmd, lx, rx);
        if constexpr(cmd == 2) lx += rx;
        return lx;
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vl a(n);
    for(auto &&e : a) cin >> e;
    Segtree_beats seg(a);
    rep(q) {
        int t;
        ll l, r, b;
        cin >> t >> l >> r;
        if(t != 3) cin >> b;
        if(t == 0) seg.chmin(l, r, b);
        if(t == 1) seg.chmax(l, r, b);
        if(t == 2) seg.add(l, r, b);
        if(t == 3) cout << seg.prod_sum(l, r) << '\n';
    }
}
