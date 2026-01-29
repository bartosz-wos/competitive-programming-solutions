#include "bits/stdc++.h"

using namespace std;

void solve() {
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    s++;
    vector<int> p(n + 1, -1), l(n + 1, 1);
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i] >> l[i];
        l[i] = l[i] + 1 + l[p[i]];
        g[p[i]].push_back(i);
    }
    unordered_set<int> have;
    for (int i = 0; i <= n; i++) {
        have.insert(l[i] + s);
    }
    vector<int> ans(m);
    vector<vector<pair<int, int>>> qu(n + 1);
    for (int q = 0; q < m; q++) {
        int pr, len;
        cin >> pr >> len;
        len = k - len - l[pr];
        bool ok = false;
        if (len == 0) {
            ok = true;
        }
        qu[pr].push_back({q, len});
        len += l[pr];
        int sum = 0;
        for (int tmp = pr; tmp != -1; tmp = p[tmp]) {
            if (have.find(len - sum) != have.end()) {
                ok = true;
            }
            sum += l[tmp] - (tmp != 0 ? l[p[tmp]] : 0);
        }
        ans[q] = ok;
    }
    vector<int> ms((int) 1e6);
    auto dfs = [&] (auto&& dfs, int v, int cur) -> void {
        if (cur < (int) ms.size()) {
            ms[cur]++;
        }
        for (auto u : g[v]) {
            dfs(dfs, u, cur + l[u] - l[v]);
        }
    };
    auto dfs2 = [&] (auto&& dfs2, int v, int cur) -> void {
        if (cur < (int) ms.size()) {
            ms[cur]--;
        }
        for (auto u : g[v]) {
            dfs2(dfs2, u, cur + l[u] - l[v]);
        }
    };
    auto go = [&] (auto&& go, int v) -> void {
        dfs(dfs, v, s);
        for (auto [q, x] : qu[v]) {
            for (int i = 1; i * i <= x; i++) {
                if (x % i == 0) {
                    if (ms[i] || ms[x / i]) {
                        ans[q] = 1;
                    }
                }
            }
        }
        for (auto u : g[v]) {
            go(go, u);
        }
        dfs2(dfs2, v, s);
    };
    go(go, 0);
    for (auto ok : ans) {
        cout << (ok ? "YES\n" : "NO\n");
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
//    cin >> t;
    while (t--) {
        solve();
    }
}
