#include "bits/stdc++.h"

#ifndef ONLINE_JUDGE
#include "./debug/debug.h"
#endif

using namespace std;
typedef long long ll;
// typedef __int128 lll;

const int inf = 1e8;

void chmx(int n, int& mx1, int& mx2) {
    if (n > mx1) {
        mx2 = mx1;
        mx1 = n;
    } else mx2 = max(mx2, n);
}

void solve() {
    int N;
    cin >> N;
    vector<array<int, 2>> adj[N];
    for (int i = 0; i < N - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({ v, w });
        adj[v].push_back({ u, w });
    }

    vector<array<int, 2>> dp(N, { 0 });
    function<void(int, int)> dfs1 = [&](int v, int p) {
        int mx = -inf;
        for (auto [ch, w] : adj[v]) {
            if (ch == p) continue;
            dfs1(ch, v);
            auto [a1, a2] = dp[ch];
            int cur = max(a2, a1 + w);
            dp[v][1] += cur;
            mx = max(a2 + w - cur, mx);
        }
        dp[v][0] = dp[v][1] + mx;
        return dp[v];
        };
    dfs1(0, -1);

    vector<int> ans(N);

    function<void(int, int, array<int, 2>&)> dfs2 = [&](int v, int p, array<int, 2>& fr_p) {
        int mx1 = -inf, mx2 = -inf;
        int na2 = 0;
        if (p != -1) dp[p] = fr_p;
        for (auto [ch, w] : adj[v]) {
            auto [a1, a2] = dp[ch];
            int cur = max(a2, a1 + w);
            na2 += cur;
            chmx(a2 + w - cur, mx1, mx2);
        }
        ans[v] = na2 + max(0, mx1 + mx2);
        ll mx12 = 0ll + mx1 + mx2;
        for (auto [ch, w] : adj[v]) {
            if (ch == p) continue;
            auto [a1, a2] = dp[ch];
            array<int, 2> to_ch;
            int cur = max(a2, a1 + w);
            to_ch[1] = na2 - cur;
            int d = a2 + w - cur;
            to_ch[0] = to_ch[1] + mx12 - max(mx2, d);
            dfs2(ch, v, to_ch);
        }
        };
    array<int, 2> ne;
    dfs2(0, -1, ne);
    cout << *max_element(ans.begin(), ans.end()) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int tt = 1;
    // cin >> tt;

    while (tt--)
        solve();
}

