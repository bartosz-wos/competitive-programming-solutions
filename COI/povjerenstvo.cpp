#include <bits/stdc++.h>
using namespace std;

#define fs first
#define sc second
#define mp make_pair
#define FOR(i, j, k) for (int i = j, Z = k; i < Z; i++)
using ll = long long;
typedef pair<int, int> pii;

const int MXN = 500005;
int n, m;
vector<int> edge[MXN];
bool ban[MXN];
vector<int> ans;

void solve() {
    int x, y;
    cin >> n >> m;
    while (m--) {
        cin >> x >> y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    FOR(id, 1, n + 1) {
        if (ban[id]) continue;
        ans.push_back(id);
        for (auto &i : edge[id]) ban[i] = true;
    }
    cout << ans.size() << '\n';
    for (auto &i : ans) cout << i << ' ';
    cout << '\n';
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solve();
    return 0;
}
