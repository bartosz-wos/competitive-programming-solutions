#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back

vector<vector<pair<int, int>>> weights;
vector<int> p;

const int MAX_N = 1e5;

int parent[MAX_N + 5], sz[MAX_N + 5];

int find (int x) {
  while (x != parent[x]) {
    x = parent[x];
  }
  return x;
}

bool same (int a, int b) {
  return find(a) == find(b);
}

bool unite (int a, int b) {
  a = find(a);
  b = find(b);
  if (a == b) {
    return false;
  }
  if (sz[a] < sz[b]) {
    swap(a, b);
  }

  /* a -> bigger, b -> smaller */
  sz[a] += sz[b];
  parent[b] = a;
  return true;
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, i, j, max_val, weight, ans;

  cin >> n;

  p = vector<int>(n + 1);
  for (i = 1; i <= n; i++) {
    cin >> p[i];
    parent[i] = i;
    sz[i] = 1;
  }

  sort(p.begin() + 1, p.end());
  p.erase(unique(p.begin() + 1, p.end()), p.end());

  n = p.size() - 1;
  weights = vector<vector<pair<int, int>>>(p[n] + 5);
  for (i = 1; i <= n; i++) {
    j = i + 1;
    for (max_val = p[i]; max_val <= p[n]; max_val += p[i]) {
      while (j <= n && p[j] < max_val) {
        j++;
      }
      if (j > n) {
        continue;
      }
      weights[p[j] % p[i]].push_back(make_pair(i, j));
    }
  }
  ans = 0;
  for (weight = 0; weight <= p[n]; weight++) {
    for (auto &x : weights[weight]) {
      if (unite(x.first, x.second)) {
        ans += weight;
      }
    }
  }
  cout << ans << "\n";
  return 0;
}
