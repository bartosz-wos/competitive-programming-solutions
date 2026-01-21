#include <bits/stdc++.h>
using namespace std;
using i32 = int;
#define len(x) (int)(x.size())
template<typename T>
using vec = vector<T>;

vector<i32> find_reachable(vector<i32> r, vector<i32> u1, vector<i32> v1, vector<i32> c) {
    int n = len(r);
    vec<vec<pair<int, int>>> g(n);
    for (int i = 0; i < len(u1); i++) {
        g[u1[i]].emplace_back(v1[i], c[i]);
        g[v1[i]].emplace_back(u1[i], c[i]);
    }
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    for (int i = 0; i < n; i++) {
        shuffle(g[i].begin(), g[i].end(), rng);
    }
    vec<int> key_set;
    vec<vec<int>> destinations(n);
    vec<bool> keys(n, false);
    vec<bool> keys1(n, false);

    auto clean = [&]() {
        for (auto x: key_set) {
            keys[x] = false;
            keys1[x] = false;

            vec<int>().swap(destinations[x]);
//            destinations[x].clear();
        }
        key_set.clear();
    };
    vec<i32> ans(n, 1e9);
    i32 cur_min = 1e9;
    vec<bool> was(n, false);
    auto solve = [&](int start) -> int {
        clean();
        queue<int> q;

        vec<bool> ok(n, false);
        auto add_key = [&](int x) -> int {
            if (keys[x]) return 0;
            keys[x] = true;
            key_set.push_back(x);
            for (auto t: destinations[x]) {
                if(ok[t]) continue;
                if (was[t]) {
                    return -1;
                }
                q.push(t);
            }
            return 0;
        };
        q.push(start);
        int cnt = 0;
        add_key(r[start]);
        vec<int> vis;
        while (!q.empty()) {
            auto v = q.front();
            q.pop();
            vis.push_back(v);

            if (ok[v]) continue;
            ok[v] = true;
            cnt++;
            if (add_key(r[v]) == -1) {
                return 1e9;
            }
            for (auto [u, tc]: g[v]) {
                if (ok[u]) continue;
                if (keys[tc]) {
                    if (was[u]) {
                        return 1e9;
                    }
                    q.push(u);
                } else {
                    destinations[tc].push_back(u);
                    if (!keys1[tc]) {
                        keys1[tc] = true;
                        key_set.push_back(tc);
                    }
                }
            }
            if (cnt > cur_min) {
                return 1e9;
            }
        }
        for (auto x: vis) {
            ans[x] = min(ans[x], cnt);
        }
        return cnt;
    };

    vec<int> perm;
    for (int i = 0; i < len(u1); i++) {
        perm.push_back(u1[i]);
        perm.push_back(v1[i]);
    }


    shuffle(perm.begin(), perm.end(), rng);

    for (auto i: perm) {
        if(was[i]) continue;
        solve(i);
        was[i] = true;
        cur_min = min(cur_min, ans[i]);
    }
    for (int i = 0; i < n; i++) {
        if (!was[i]) {
            solve(i);
        }
    }

    int min_val = *min_element(ans.begin(), ans.end());
    for (int i = 0; i < n; i++) {
        ans[i] = ans[i] == min_val;
    }
    return ans;
}
