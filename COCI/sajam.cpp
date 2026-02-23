#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
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
template<class T> int lwb(V<T>& a, const T& b) { return lb(all(a),b)-begin(a); }
template<class T> int upb(V<T>& a, const T& b) { return ub(all(a),b)-begin(a); }
template<class T> bool ckmin(T& a, const T& b) { return a > b ? a=b, true : false; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a=b, true : false; }
#define pct __builtin_popcount
#define ctz __builtin_ctz
#define clz __builtin_clz
constexpr int p2(int x) { return (int)1 << x; }
constexpr int bits(int x) { return x == 0 ? 0 : 31-clz(x); } // floor(log2(x)) 

const int N = 1000;
bitset<N> row[N];

void solve() {
    int n, k; cin >> n >> k;

    if (n == 1) {
        cout << "DA\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; cin >> c;
            if (c == 'o') row[i].set(j);
        }
    }

    if (k == n) {
        for (int i = 0; i < n; i++) {
            row[0].flip(i);

            int cost = 0;
            for (int j = 1; j < n; j++) {
                int cnt = (row[j]^row[0]).count();
                cost += min(cnt, n-cnt);
            }

            row[0].flip(i);

            if (cost <= k-1) {
                cout << "DA\n";
                return;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int cost = 0;
        for (int j = 0; j < n; j++) if (j != i) {
            int cnt = (row[i]^row[j]).count();
            cost += min(cnt, n-cnt);
        }
        if (cost <= k) {
            cout << "DA\n";
            return;
        }
    }
    cout << "NE\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
