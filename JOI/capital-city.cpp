#include <bits/stdc++.h>
#define ll long long
// #define int long long
#define pb push_back
#define F first
#define S second
#define mp make_pair
#define pii pair <int, int>
#define smin(x, y) (x) = min((x), (y))
#define smax(x, y) (x) = max((x), (y))
#define all(x) (x).begin(), (x).end()
using namespace std;
 
const int inf = 1e9+7;
const int mod = 998244353;
const int maxn = 2e5+5;
 
int n, k, c[maxn], sz[maxn], par[maxn], id[maxn];
bool mark[maxn], vis[maxn];
vector <int> adj[maxn], vec[maxn];
queue <int> q;
 
void dfs1(int v, int p) {
    sz[v] = 1;
    vis[c[v]] = 1;
    for (int u : adj[v]) {
        if (!mark[u] and u != p) {
            dfs1(u, v); sz[v] += sz[u];
        }
    }
}
 
void dfs2(int v, int p, int r) {
    par[v] = p, id[v] = r;
    for (int u : adj[v]) {
        if (!mark[u] and u != p) dfs2(u, v, r);
    }
}
 
int fcen(int v, int p, int s) {
    for (int u : adj[v]) {
        if (!mark[u] and u != p and sz[u]*2 > s) return fcen(u, v, s);
    }
    return v;
}
 
int cen(int v) {
    dfs1(v, v);
    v = fcen(v, v, sz[v]);
    dfs2(v, v, v); 
    int ans = 0;
    q.push(c[v]);
    while (q.size()) {
        int col = q.front(); q.pop();
        if (!vis[col]) continue;
        vis[col] = 0;
        for (int u : vec[col]) {
            if (id[u] != v) {
                ans = k; break;
            }
            q.push(c[par[u]]);
        }
        ans++;
    }
    mark[v] = 1;
    for (int u : adj[v]) {
        if (!mark[u]) smin(ans, cen(u));
    }
    return ans;
}
 
int32_t main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int v, u; cin >> v >> u;
        adj[--v].pb(--u);
        adj[u].pb(v);
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i]; vec[--c[i]].pb(i);
    }
    cout << cen(0)-1 << '\n';
    return 0;
}
