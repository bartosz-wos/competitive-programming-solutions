#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("avx2")

#define int int64_t
const int inf=1e18;

#ifdef LOCAL
#include "algo/debug.h"
#else
template <typename... Args>
void dummy(Args&&... args){}
#define ps dummy
#endif

#define f first
#define s second
template<class T> using V = vector<T>; 
using vi = V<int>;
using vb = V<bool>;
using vs = V<string>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x) 
#define len(x) (int)((x).size())
#define rsz resize
#define ins insert
#define ft front()
#define bk back()
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define ai2 array<int,2>
#define ai3 array<int,3>
#define ai4 array<int,4>
#define ai5 array<int,5>
template<class T> int lwb(const V<T>& a, const T& b) { return lb(all(a),b)-begin(a); }
template<class T> int upb(const V<T>& a, const T& b) { return ub(all(a),b)-begin(a); }
template<class T> bool ckmin(T& a, const T& b) { return a > b ? a=b, true : false; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a=b, true : false; }
#define pct __builtin_popcountll
#define ctz __builtin_ctzll
#define clz __builtin_clzll
constexpr int p2(int x) { return (int)1 << x; }
constexpr int bits(int x) { return x == 0 ? 0 : 63-clz(x); } // floor(log2(x)) 
template<class T>void UNIQUE(V<T>& v) { sort(all(v)); v.erase(unique(all(v)),end(v)); }
template<class T,class U>void erase(T& t, const U& u) { auto it = t.find(u); assert(it != end(t)); t.erase(it); }
template<class F> struct y_combinator_result {
    F f;
    template<class T> explicit y_combinator_result(T &&f): f(std::forward<T>(f)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...args) { return f(std::ref(*this), std::forward<Args>(args)...); }
};
template<class Fun> decltype(auto) yy(Fun &&fun) { return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun)); }

int n;
string s;
int asked = 0;

bool ask(int l, int r) {
    if (l < 0 || r >= n) return false;
#ifdef LOCAL
    bool pal = true;
    for (int i = l; i <= r; i++) {
        pal &= s[i] == s[r - (i - l)];
    }
    asked++;
    return pal;
#else
    cout << "? " << l + 1 << ' ' << r + 1 << endl;
    bool res; cin >> res;
    return res;
#endif
}

void solve() {
#ifdef LOCAL
    cin >> s;
    n = len(s);
#else
    cin >> n;
#endif

    int ans = 1;
    for (int i = 0; i < n; i++) {
        while (ask(i - (ans / 2 + 1), i + (ans / 2 + 1))) {
            ans += 2;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        while (ask(i - (ans / 2), i + (ans / 2 + 1))) {
            ans = 2 * (ans / 2 + 1);
        }
    }

    cout << "! " << ans << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
