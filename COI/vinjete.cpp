#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 1;
vector<array<int, 3>> g[N];
int t[N * 120], L[N * 120], R[N * 120], nxt;
int res[N], root[N], n, m;

int upd(int v, int l, int r, int ql, int qr) {
    int vn = ++nxt;
    if (ql <= l and r <= qr) t[vn] = r - l + 1;
    else {
        int m = (l + r) / 2;
        L[vn] = L[v], R[vn] = R[v];
        if (ql <= m) L[vn] = upd(L[v], l, m, ql, qr);
        if (m < qr) R[vn] = upd(R[v], m + 1, r, ql, qr);
        t[vn] = max(t[v], t[L[vn]] + t[R[vn]]);
    }
    return vn;
}

void dfs(int u, int p) {
    for (auto [v, l, r] : g[u])
        if (v != p) {
            root[v] = upd(root[u], 1, m, l, r);
            res[v] = t[root[v]];
            dfs(v, u);
        }
}


void _main() {
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, l, r; cin >> u >> v >> l >> r;
        g[u].push_back({v, l, r});
        g[v].push_back({u, l, r});
    }
    dfs(1, 0);
    for (int i = 2; i <= n; i++) cout << res[i] << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(0);
    { _main(); cout << '\n'; }
}
