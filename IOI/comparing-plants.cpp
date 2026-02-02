#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define all(a) (a).begin(), (a).end()
#define replr(i, a, b) for (int i = int(a); i <= int(b); ++i)
#define reprl(i, a, b) for (int i = int(a); i >= int(b); --i)
#define rep(i, n) for (int i = 0; i < int(n); ++i)
#define mkp(a, b) make_pair(a, b)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<PII> VPI;
typedef vector<VI> VVI;
typedef vector<VVI> VVVI;
typedef vector<VPI> VVPI;
typedef pair<ll, ll> PLL;
typedef vector<ll> VL;
typedef vector<PLL> VPL;
typedef vector<VL> VVL;
typedef vector<VVL> VVVL;
typedef vector<VPL> VVPL;
template<class T> T setmax(T& a, T b) {if (a < b) return a = b; return a;}
template<class T> T setmin(T& a, T b) {if (a < b) return a; return a = b;}
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<class T>
using indset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
#include "plants.h"

struct MINARGSEGTREE {
    int n;
    VPI tree;
    VI lazy;
    MINARGSEGTREE(){}
    MINARGSEGTREE(int sz) {
        n = 1;
        while (n < sz) n *= 2;
        tree = VPI(2*n, {+1e9, -1});
        lazy = VI(2*n);
    }
    void push(int N) {
        tree[N].ff += lazy[N];
        if (2*N+2 < 2*n) {
            lazy[2*N+1] += lazy[N];
            lazy[2*N+2] += lazy[N];
        }
        lazy[N] = 0;
    }
    void set(int N, int L, int R, int i, PII s) {
        push(N);
        if (i < L || i > R) return;
        if (L == R) {
            tree[N] = s;
            return;
        }
        int M = (L + R) / 2;
        set(2*N+1, L, M, i, s);
        set(2*N+2, M+1, R, i, s);
        tree[N] = min(tree[2*N+1], tree[2*N+2]);
    }
    void add(int N, int L, int R, int l, int r, int s) {
        push(N);
        if (R < l || L > r) return;
        if (l <= L && R <= r) {
            lazy[N] = s;
            push(N);
            return;
        }
        int M = (L + R) / 2;
        add(2*N+1, L, M, l, r, s);
        add(2*N+2, M+1, R, l, r, s);
        tree[N] = min(tree[2*N+1], tree[2*N+2]);
    }
    PII get(int N, int L, int R, int l, int r) {
        push(N);
        if (l <= L && R <= r) return tree[N];
        if (R < l || L > r) return {+1e9, -1};
        int M = (L + R) / 2;
        return min(get(2*N+1, L, M, l, r), get(2*N+2, M+1, R, l, r));
    }
    void set(int i, int s) {
        set(0, 0, n-1, i, {s, i});
    }
    void add(int l, int r, int s) {
        add(0, 0, n-1, l, r, s);
    }
    PII get(int l, int r) {
        return get(0, 0, n-1, l, r);
    }
};
struct FIRSTZERODS {
    int n;
    MINARGSEGTREE seg;
    FIRSTZERODS(){}
    FIRSTZERODS(VI a) {
        n = a.size();
        seg = MINARGSEGTREE(n);
        rep(i, n) seg.set(i, a[i]);
    }
    void remove(int i) {
        seg.set(i, +1e9);
    }
    void decrement(int l, int r) {
        l = (l+100*n)%n;
        r = (r+100*n)%n;
        if (l <= r) seg.add(l, r, -1);
        else {
            seg.add(l, n-1, -1);
            seg.add(0, r, -1);
        }
    }
    int get(int l, int r) {
        l = (l+100*n)%n;
        r = (r+100*n)%n;
        PII ret;
        if (l <= r) ret = seg.get(l, r);
        else {
            ret = seg.get(l, n-1);
            if (ret.ff) ret = seg.get(0, r);
        }
        if (ret.ff == 0) return ret.ss;
        return -1;
    }
    void print() {
        rep(i, n) cout << seg.get(i, i).ff << " "; cout << endl;
    }
};

int n, k;
FIRSTZERODS seg;
VI a;
int mx;

void extract(int i) {
    while (true) {
        int prev = seg.get(i-k+1, i-1);
        if (prev == -1) break;
        extract(prev);
    }
    a[i] = mx--;
    seg.remove(i);
    seg.decrement(i-k+1, i-1);
}

VI b;
VI pr, pl;
VVI parr, parl;

void init(int K_ARG, VI r) {
    k = K_ARG;
    n = r.size();
    seg = FIRSTZERODS(r);
    a = VI(n, -1);
    mx = n-1;
    while (mx >= 0) extract(seg.get(0, n-1));
    rep(_, 3) for (int x : a) b.pb(x);
    pr = pl = VI(3*n);
    rep(i, 3*n) pr[i] = pl[i] = i;
    set<PII> st;
    replr(i, 0, k-1) st.insert({b[i], i});
    replr(i, 0, 3*n-1) {
        auto it = st.upper_bound({b[i], +2e9});
        if (it != st.end()) pr[i] = it->ss;
        st.erase({b[i], i});
        if (i+k < 3*n) st.insert({b[i+k], i+k});
    }
    st = set<PII>();
    reprl(i, 3*n-1, 3*n-k) st.insert({b[i], i});
    reprl(i, 3*n-1, 0) {
        auto it = st.upper_bound({b[i], +2e9});
        if (it != st.end()) pl[i] = it->ss;
        st.erase({b[i], i});
        if (i-k >= 0) st.insert({b[i-k], i-k});
    }
    parr = parl = VVI(3*n, VI(21));
    rep(i, 3*n) {
        parr[i][0] = pr[i];
        parl[i][0] = pl[i];
    }
    replr(k, 1, 20) {
        rep(i, 3*n) {
            parl[i][k] = parl[parl[i][k-1]][k-1];
            parr[i][k] = parr[parr[i][k-1]][k-1];
        }
    }
}

bool goright(int x, int y) {
    reprl(k, 20, 0) if (parr[x][k] < y) x = parr[x][k];
    return y <= x+k-1 && b[y] > b[x];
}
bool goleft(int x, int y) {
    reprl(k, 20, 0) if (parl[x][k] > y) x = parl[x][k];
    return x <= y+k-1 && b[y] > b[x];
}
bool issmaller(int x, int y) {
    if (y > x) return goright(x, y) || goleft(x, y-n);
    return goright(x, y+n) || goleft(x, y);
}

int compare_plants(int x, int y) {
    x += n;
    y += n;
    if (issmaller(x, y)) return -1;
    if (issmaller(y, x)) return +1;
    return 0;
}




