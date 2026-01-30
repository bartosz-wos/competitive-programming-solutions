#include <bits/stdc++.h>
 
#define int long long 
 
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
 
#define F first 
#define S second
#define mp make_pair
#define pb push_back
#define all(x) x.begin(), x.end()
#define kill(x) cout << x << "\n", exit(0);
#define pii pair<int, int>
#define pll pair<long long, long long>
#define endl "\n"
 
 
 
using namespace std;
typedef long long ll;
// typedef __int128_t lll;
typedef long double ld;
 
 
const int MAXN = (int)1e6 + 7;
const int MOD = (int)1e9 + 7;
const ll INF = (ll)1e9 + 7;
 
 
int n, m, k, tmp, t, tmp2, tmp3, tmp4, u, v, w, flag, q, ans, N, X, Y;
int arr[MAXN], h[MAXN], par[MAXN], sar[MAXN], deg[MAXN], st[MAXN], ft[MAXN], sz[MAXN], R, barg, cnt[MAXN], ind[MAXN];
vector<int> adj[MAXN], vec, old_barg;
vector<pii> child[MAXN];


/* Segment Tree */
#define mid ((l+r)>>1)
#define lid (id<<1)
#define rid (lid|1)



pii seg[MAXN<<2];
bool lazy[MAXN<<2];


inline pii merge(pii x, pii y) { return {x.F+y.F, x.S+y.S}; }

inline void relax(int l, int r, int id) {
    if (!lazy[id]) return;

    swap(seg[lid].F, seg[lid].S); lazy[lid] ^= 1;
    swap(seg[rid].F, seg[rid].S); lazy[rid] ^= 1;

    lazy[id] = 0;
}


void build(int l=0, int r=n, int id=1) {
    if (l+1 == r) {
        if (cnt[ind[l]]&1) seg[id].S++;
        else seg[id].F++;

        return;
    }

    build(l, mid, lid); build(mid, r, rid);

    seg[id] = merge(seg[lid], seg[rid]);
}


void upd(int s, int t, int l=0, int r=n, int id=1) {
    if (s >= t) return;

    if (s <= l && t >= r) {
        swap(seg[id].F, seg[id].S); lazy[id] ^= 1;
        return;
    }

    relax(l, r, id);

    if (s < mid) upd(s, t, l, mid, lid);
    if (t > mid) upd(s, t, mid, r, rid);

    seg[id] = merge(seg[lid], seg[rid]);
}

/* Segment Tree */
 

void DFSsz(int v) {
    sz[v] = 1; cnt[v] = (deg[v] == 1);

    for (int u:adj[v]) {
        if (u == par[v]) continue;

        par[u] = v; h[u] = h[v]+1;
        
        DFSsz(u); 
        
        sz[v] += sz[u]; child[v].pb({sz[u], u}); cnt[v] += cnt[u];
    }
}


void DFS(int v, int b) {
    sar[v] = b; sort(all(child[v]), greater<pii>());
    ind[flag] = v; st[v] = flag++;

    for (int i=0; i<child[v].size(); i++) {
        int u = child[v][i].S;

        if (!i) DFS(u, b);
        else DFS(u, u);
    }
}


inline void delta_deg(int v, int k) {
    barg -= (deg[v] == 1);
    deg[v] += k;
    barg += (deg[v] == 1);
}


inline void root_path(int u) {
    while (u) {
        int v = sar[u];
        upd(st[v], st[u]+1);
        u = par[v];
    }
}


int32_t main() {
    #ifdef LOCAL
    freopen("inp.in", "r", stdin);
    freopen("res.out", "w", stdout);
    #else
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #endif

    cin >> n >> q;

    for (int i=1; i<n; i++) {
        cin >> u >> v;

        adj[u].pb(v); adj[v].pb(u); delta_deg(u, 1); delta_deg(v, 1);
    }

    for (int i=1; i<=n; i++) if (deg[i] > 1) R = i;

    // cout << "! " << R << endl;

    DFSsz(R); DFS(R, R); build();

    while (q--) {
        cin >> k;

        for (int i=0; i<k; i++) {
            int v; cin >> v;

            if (deg[v] == 1) old_barg.pb(v), root_path(v);

            vec.pb(v); delta_deg(v, 1); root_path(v);
        }

        // cout << "@ " << barg << endl;
        // cout << n+k-1 << " " << seg[1].F << " " << !(barg&1) << endl;

        if ((barg+k)&1) cout << -1 << endl;
        else cout << (n+k-1) + seg[1].F - (((barg+k)%2) == 0) << endl;


        for (int v:vec) delta_deg(v, -1), root_path(v);
        for (int v:old_barg) root_path(v);
        vec.clear(); old_barg.clear();
    }

    return 0;
}
