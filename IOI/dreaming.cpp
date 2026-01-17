#include "dreaming.h"
#include "bits/stdc++.h"
using namespace std;
 
int travelTime(int n, int m, int L, int A[], int B[], int T[]) {
    vector<vector<pair<int, int>>> g(n);
    vector<bool> vis(n), vis2(n);
    for (int i = 0; i < m; i++) {
        g[A[i]].emplace_back(B[i], T[i]);
        g[B[i]].emplace_back(A[i], T[i]);
    }
    vector<int> h(n), dist(n), all;
    auto dfs = [&](auto &dfs, int u) -> void {
        all.emplace_back(u);
        vis[u] = true;
        for (auto [v, w]: g[u]) {
            if (vis[v]) continue;
            dfs(dfs, v);
            h[u] = max(h[u], h[v] + w);
        }
    };
    auto dfs2 = [&](auto &dfs2, int u, int came) -> void {
        // cout << '\t' << u << ' ' << came << endl;
        vis2[u] = true;
        int mx1 = 0, mx2 = 0;
        for (auto [v, w]: g[u]) {
            if (vis2[v]) continue;
            if (mx1 < h[v] + w) {
                mx2 = mx1;
                mx1 = h[v] + w;
            } else {
                mx2 = max(mx2, h[v] + w);
            }
        }
        dist[u] = max(came, h[u]);
        for (auto [v, w]: g[u]) {
            if (vis2[v]) continue;
            if (mx1 == h[v] + w) {
                dfs2(dfs2, v, max(came, mx2) + w);
            } else {
                dfs2(dfs2, v, max(came, mx1) + w);
            }
        }
    };
    multiset<int, greater<>> st;
    vector<int> shit;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        dfs(dfs, i);
        dfs2(dfs2, i, 0);
        int mn = 1e9;
        for (int u: all) mn = min(mn, dist[u]);
        shit.emplace_back(mn);
        st.insert(mn);
        all.clear();
    }
    int ans = 2e9, dist_max = *max_element(dist.begin(), dist.end());
    if (st.size() == 1) return dist_max;
    if (st.size() == 2) {
        return max(dist_max, *st.begin() + *st.rbegin() + L);
    }
    for (int x: shit) {
        int now = dist_max;
        st.erase(st.find(x));
        now = max(now, x + L + *st.begin());
        auto it = st.begin();
        auto it2 = st.begin();
        it2++;
 
        now = max(now, *it + L + L + *it2);
        st.insert(x);
        ans = min(ans, now);
    }
    return ans;
}
