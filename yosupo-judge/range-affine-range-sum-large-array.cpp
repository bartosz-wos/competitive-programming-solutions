#include <bits/stdc++.h>
using namespace std;
using ll=long long;

constexpr int M = 998244353;

struct SparseSegmentTree {
  ll n;
  struct Node {
    int ls = 0, rs = 0;
    ll st = 0;
    pair<ll, ll> lazy = {1, 0};
  };
  
  vector<Node> tree;

  SparseSegmentTree(ll _n) : n(_n) {
    tree.reserve(6000000); 
    tree.push_back(Node());
    tree.push_back(Node());
  }

  inline int get_ls(int u) {
    if (!tree[u].ls) {
      tree[u].ls = tree.size();
      tree.push_back(Node());
    }
    return tree[u].ls;
  }

  inline int get_rs(int u) {
    if (!tree[u].rs) {
      tree[u].rs = tree.size();
      tree.push_back(Node());
    }
    return tree[u].rs;
  }

  inline void push(int u, long long s, ll e) {
    if (tree[u].lazy.first == 1 && tree[u].lazy.second == 0) return;
    ll b = tree[u].lazy.first;
    ll c = tree[u].lazy.second;
    ll len = (e - s + 1) % M;
    tree[u].st = (tree[u].st * b + c * len) % M;
    if (s != e) {
      int v = get_ls(u);
      int w = get_rs(u);
      (tree[v].lazy.first *= b) %= M;
      (tree[w].lazy.first *= b) %= M;
      tree[v].lazy.second = (tree[v].lazy.second * b + c) % M;
      tree[w].lazy.second = (tree[w].lazy.second * b + c) % M;
    }
    tree[u].lazy = {1, 0};
  }

  void update(ll l, ll r, pair<ll, ll> val, int u, ll s, ll e) {
    push(u, s, e);
    if (e < l || r < s) return;
    if (l <= s && e <= r) {
      tree[u].lazy = val;
      push(u, s, e);
      return;
    }
    ll m = s + (e - s) / 2;
    int v = get_ls(u);
    int w = get_rs(u);
    update(l, r, val, v, s, m);
    update(l, r, val, w, m + 1, e);
    tree[u].st = (tree[v].st + tree[w].st) % M;
  }

  ll query(ll l, ll r, int u, ll s, ll e) {
    if (!u) return 0LL;
    push(u, s, e);
    if (e < l || r < s) return 0LL;
    if (l <= s && e <= r) return tree[u].st;
    ll m = s + (e - s) / 2;
    auto left = query(l, r, tree[u].ls, s, m);
    auto right = query(l, r, tree[u].rs, m + 1, e);
    return (left + right) % M;
  }

  void update(ll l, ll r, pair<ll,ll> val) { update(l, r, val, 1, 0, n - 1); }
  ll query(ll l, ll r) { return query(l, r, 1, 0, n - 1); }
};

int main() {
  ios::sync_with_stdio(false); 
  cin.tie(nullptr);
  cout.tie(nullptr);
  ll n;
  int q;
  cin >> n >> q;
  SparseSegmentTree s(n);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      ll l, r, b, c;
      cin >> l >> r >> b >> c;
      s.update(l, r - 1, {b, c});
    } else {
      ll l, r;
      cin >> l >> r;
      cout << s.query(l, r - 1) << "\n";
    }
  }
}
