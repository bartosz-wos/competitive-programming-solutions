#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int N = 5e5 + 5;
const int inf = 1e18;
vector<pii>adj[N];
vector<piii>edge;
int par[N],sz[N],f[N];

void make_set(int v) {
    par[v] = v;
    sz[v] = 1;
}

int find_set(int v) {
    if (v == par[v]) return v;
    int p = find_set(par[v]);
    par[v] = p;
    return p;
}

bool union_sets(int a,int b) {
    a = find_set(a),b = find_set(b);
    if (a == b) return 0;
    if (sz[a] < sz[b]) swap(a,b);
    sz[a] += sz[b];
    par[b] = a;
    return 1;
}

void dfs(int u,int p) {
    for (auto x: adj[u]) {
        int v = x.fi,w = x.se;
        if (v == p) continue;
        f[v] = min(f[u],w);
        dfs(v,u);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n,e,q;
    cin >> n >> e >> q;
    for (int i = 1; i <= e; i++) {
        int u,v,w;
        cin >> u >> v >> w;
        edge.push_back({w,{u,v}});
    }
    sort(edge.begin(),edge.end(),greater<piii>());
    for (int i = 1; i <= n; i++) make_set(i);
    for (auto x: edge) {
        int u = x.se.fi,v = x.se.se,w = x.fi;
        if (union_sets(u,v)) {
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
    }
    f[1] = inf;
    dfs(1,-1);
    while (q--) {
        int u;
        cin >> u;
        cout << f[u] << "\n";
    }
}
