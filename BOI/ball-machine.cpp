#include "bits/stdc++.h"

using namespace std;

#ifdef duc_debug
#include "bits/debug.h"
#else
#define debug(...)
#endif

const int maxn = 1e5 + 5;
const int LG = 18;
int n, q, root;
vector<int> g[maxn];
int h[maxn], par[maxn];
int tin[maxn], tout[maxn], timer, et[maxn];
int up[maxn][LG + 1];
int mvt[maxn];

void pre_dfs(int u) {
  mvt[u] = u;
  for (auto v : g[u]) {
    h[v] = h[u] + 1;
    up[v][0] = u;
    for (int i = 1; i <= LG; ++i) {
      up[v][i] = up[up[v][i - 1]][i - 1];
    }
    pre_dfs(v);
    mvt[u] = min(mvt[u], mvt[v]);
  }
  sort(g[u].begin(), g[u].end(), [](const int &x, const int &y) -> bool {
    return mvt[x] < mvt[y];
  });
}

void dfs(int u) {
  tin[u] = timer;
  for (auto v : g[u]) {
    dfs(v);
  }
  tout[u] = ++timer;
  et[timer] = u;
}

int bit[maxn];

void upd(int i, int val) {
  val = -val;
  for (; i <= n; i += i & (-i)) {
    bit[i] += val;
  }
}

int lower_bound(long long v) {
  long long sum = 0;
  int pos = 0;
  for (int i = LG; i >= 0; i--) {
    if (pos + (1 << i) <= n and sum + bit[pos + (1 << i)] < v) {
      sum += bit[pos + (1 << i)];
      pos += (1 << i);
    }
  }
  return pos + 1;
}

int get(int i) {
  int ans = 0;
  for (; i > 0; i -= i & (-i)) {
    ans += bit[i];
  }
  return ans;
}

void solve() {
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> par[i];
    if (par[i] == 0) root = i;
    else g[par[i]].push_back(i);
  }
  pre_dfs(root);
  dfs(root);
  
  for (int i = 1; i <= n; ++i) {
    upd(i, -1);
  }
  
  while (q--) {
    int op; cin >> op;
    if (op == 1) {
      int k; cin >> k;
      int cur = 0;
      for (int i = 1; i <= k; ++i) {
        cur = lower_bound(1);
        upd(cur, 1);
      }
      cout << et[cur] << '\n';
    } else {
      int u; cin >> u;
      int res = 0;
      for (int i = LG; i >= 0; --i) {
        if (up[u][i] and get(tout[up[u][i]]) == get(tout[up[u][i]] - 1)) {
          res ^= (1 << i);
          u = up[u][i];
        }
      }
      upd(tout[u], -1);
      cout << res << '\n';
    }
  }
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  solve();

  return 0;
}



