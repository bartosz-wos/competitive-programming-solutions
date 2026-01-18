#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
 
#define long                unsigned long 
#define pb                  push_back
#define mp                  make_pair
#define all(v)              (v).begin(),(v).end()
#define rall(v)             (v).rbegin(),(v).rend()
#define lb                  lower_bound
#define ub                  upper_bound
#define sz(v)               int((v).size())
#define do_not_disturb      ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define endl                '\n'
 
const int N = 1e5+7;
set <pair <int, ll>> graph[N];
vector <pair <pii, ll>> edges;
vector <vector <ll>> tree(N), lz(N);
multiset <ll, greater <ll>> to_leaves[N];
int subtree[N], level[N], parent[N][20], timer, par[N], S[N];
pii ranges[N][20];
int n, q;
ll w;
 
void push(int i, int v, int l, int r) {
    if (lz[i][v] != 0) {
        tree[i][v] += lz[i][v];
        if (l != r) {
            lz[i][v*2] += lz[i][v];
            lz[i][v*2+1] += lz[i][v];
        }
        lz[i][v] = 0;
    }
}
 
void update(int i, int v, int l, int r, int ql, int qr, ll val) {
    push(i, v, l, r);
    if (ql > r || l > qr) return;
    if (ql <= l && r <= qr) {
        lz[i][v] += val;
        push(i, v, l, r);
        return;
    }
    int mid = (l+r) >> 1;
    update(i, v*2, l, mid, ql, qr, val);
    update(i, v*2+1, mid+1, r, ql, qr, val);
    tree[i][v] = max(tree[i][v*2], tree[i][v*2+1]);
}
 
ll get(int i, int v, int l, int r, int ql, int qr) {
    push(i, v, l, r);
    if (ql > r || l > qr) return -1e18;
    if (ql <= l && r <= qr) return tree[i][v];
    int mid = (l+r) >> 1;
    return max(get(i, v*2, l, mid, ql, qr), get(i, v*2+1, mid+1, r, ql, qr));
}
 
void find_subtrees(int v, int p) {
    subtree[v] = 1;
    for (auto to : graph[v]) {
        if (to.first == p || level[to.first]) continue;
        find_subtrees(to.first, v);
        subtree[v] += subtree[to.first];
    }
}
 
int find_centroid(int v, int p, int saizu) {
    for (auto to : graph[v]) {
        if (to.first == p || level[to.first]) continue;
        if (subtree[to.first]*2 > saizu) return find_centroid(to.first, v, saizu);
    }
    return v;
}
 
ll tmpddd;
ll ans_tree[N*4];
void ans_update(int v, int l, int r, int pos, ll val) {
    if (l == r) {
        ans_tree[v] = val;
        return;
    }
    int mid = (l+r) >> 1;
    if (pos <= mid) ans_update(v*2, l, mid, pos, val);
    else ans_update(v*2+1, mid+1, r, pos, val);
    ans_tree[v] = max(ans_tree[v*2], ans_tree[v*2+1]);
}
 
void cnd_dfs(int v, int p, ll dist, int &origin, int &saizu, int &lev, int &origin2) {
    pii range;
    range.first = ++timer;
    tmpddd = max(tmpddd, dist);
    update(origin, 1, 0, saizu-1, timer, timer, dist);
    parent[v][lev] = origin2;
    
    for (auto to : graph[v]) {
        if (to.first == p || level[to.first]) continue;
        cnd_dfs(to.first, v, dist+to.second, origin, saizu, lev, origin2);
    }
    range.second = timer;
    ranges[v][lev] = range;
}
 
void centroid_decomposition(int v, int p = 0, int lev = 1) {
    find_subtrees(v, v);
    auto centroid = find_centroid(v, v, subtree[v]);
    level[centroid] = lev;
    par[centroid] = p;
    
    tree[centroid].resize(subtree[v]*4);
    lz[centroid].resize(subtree[v]*4);
    S[centroid] = subtree[v];
    timer = 0;
    for (auto to : graph[centroid]) {
        if (level[to.first]) continue;
        tmpddd = 0;
        cnd_dfs(to.first, centroid, to.second, centroid, subtree[v], lev, to.first);
        to_leaves[centroid].insert(tmpddd);
    }
    ll res = 0, cnt = 0;
    for (auto to : to_leaves[centroid]) {
        res += to;
        if (++cnt > 1) break;
    }
    ans_update(1, 1, n, centroid, res);
    
    for (auto to : graph[centroid]) {
        if (level[to.first]) continue;
        centroid_decomposition(to.first, centroid, lev+1);
    }
}
 
void solve() {
    cin >> n >> q >> w;
    for (int i = 0; i < n-1; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        if (a > b) swap(a, b);
        edges.pb(mp(mp(a, b), c));
        graph[a].insert(mp(b, c));
        graph[b].insert(mp(a, c));
    }
    centroid_decomposition(1);
    ll last = 0;
    while (q--) {
        ll d, e;
        cin >> d >> e;
        d = (d + last) % (n - 1);
        e = (e + last) % w; 
        auto a = edges[d].first.first, b = edges[d].first.second;
        auto &c = edges[d].second;
        if (level[a] > level[b]) swap(a, b);
        auto x = a;
        while (x) {
            {
                auto ita = ranges[a][level[x]].first;
                auto itb = ranges[b][level[x]].first;
                if (get(x, 1, 0, S[x]-1, ita, ita) > get(x, 1, 0, S[x]-1, itb, itb)) swap(a, b);
            }
            auto range = ranges[b][level[x]];
            auto prange = ranges[parent[b][level[x]]][level[x]];
            to_leaves[x].erase(to_leaves[x].find(get(x, 1, 0, S[x]-1, prange.first, prange.second)));
            update(x, 1, 0, S[x]-1, range.first, range.second, e-c);
            to_leaves[x].insert(get(x, 1, 0, S[x]-1, prange.first, prange.second));
            ll res = 0, cnt = 0;
            for (auto to : to_leaves[x]) {
                res += to;
                if (++cnt > 1) break;
            }
            ans_update(1, 1, n, x, res);
            x = par[x];
        }
        cout << ans_tree[1] << endl;
        c = e;
        last = ans_tree[1];
    }
}
 
int main() {
    do_not_disturb
    int t = 1;
    //~ cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
