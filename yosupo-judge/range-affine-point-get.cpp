#include <bits/stdc++.h>

using namespace std;

const int M = 998244353;

struct SegmentTree {
  int n;
  vector<long long> a, st;
  vector<pair<long long, long long>> lazy;

  SegmentTree(vector<int> &arr)
    : n(arr.size()),
    a(arr.begin(), arr.end()),
    st(arr.size() * 4),
    lazy(arr.size() * 4, {1, 0}) {}
  
  inline auto func(long long x, long long y) {
    return (x + y) % M;
  }

  inline void push(int u, int s, int e) {
    if (lazy[u].first == 1 and lazy[u].second == 0) return;
    int v = 2 * u, w = v + 1;
    st[u] = (st[u] * lazy[u].first + lazy[u].second * (e - s + 1)) % M;
    if (s != e) {
      (lazy[v].first *= lazy[u].first) %= M;
      (lazy[w].first *= lazy[u].first) %= M;
      lazy[v].second = (lazy[u].first * lazy[v].second + lazy[u].second) % M;
      lazy[w].second = (lazy[u].first * lazy[w].second + lazy[u].second) % M;
    }
    lazy[u] = {1, 0};
  }

  void build(int u, int s, int e) {
    if (s == e) {
      st[u] = a[s];
      return;
    }
    int v = 2 * u, w = v + 1, m = (s + e) / 2;
    build(v, s, m);
    build(w, m + 1, e);
    st[u] = func(st[v], st[w]);
  }


  auto query(int l, int r, int u, int s, int e) {
    push(u, s, e);
    if (e < l or r < s) return 0ll;
    if (l <= s and e <= r) return st[u];
    int v = 2 * u, w = v + 1, m = (s + e) / 2;
    auto left = query(l, r, v, s, m);
    auto right = query(l, r, w, m + 1, e);
    return func(left, right);
  }

  void update(int l, int r, pair<int, int> val, int u, int s, int e) {
    push(u, s, e);
    if (e < l or r < s) return;
    if (l <= s and e <= r) {
      lazy[u] = val;
      push(u, s, e);
      return;
    }
    int v = 2 * u, w = v + 1, m = (s + e) / 2;
    update(l, r, val, v, s, m);
    update(l, r, val, w, m + 1, e);
    st[u] = func(st[v], st[w]);
  }

  void build() { build(1, 0, n - 1); }
  auto query(int l, int r) { return query(l, r, 1, 0, n - 1); }
  void update(int l, int r, pair<int, int> val) { update(l, r, val, 1, 0, n - 1); }
};

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);

  int n, q, t;
  cin >> n >> q;
  vector<int> a(n);
  for (auto &e: a) cin >> e;

  SegmentTree s(a);

  s.build();

  while (q--) {
    cin >> t;
    if (t == 0) {
      int l, r, b, c;
      cin >> l >> r >> b >> c;
      s.update(l, r-1, {b, c});
    } else {
      int i;
      cin >> i;
      cout << s.query(i, i) << "\n";
    }
  }

  return 0;
}
