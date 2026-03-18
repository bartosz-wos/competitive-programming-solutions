#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    vector<int> stk;
    vector<int> prev(n, -1);
    for (int i = 0; i < n; i++) {
      while (!stk.empty() && a[stk.back()] <= a[i]) {
        stk.pop_back();
      }
      if (!stk.empty()) {
        prev[i] = stk.back();
      }
      stk.push_back(i);
    }
    stk.clear();
    vector<int> next(n, n);
    for (int i = n - 1; i >= 0; i--) {
      while (!stk.empty() && a[stk.back()] <= a[i]) {
        stk.pop_back();
      }
      if (!stk.empty()) {
        next[i] = stk.back();
      }
      stk.push_back(i);
    }
    stk.clear();
    vector<int> next_e(n, n);
    for (int i = n - 1; i >= 0; i--) {
      while (!stk.empty() && a[stk.back()] < a[i]) {
        stk.pop_back();
      }
      if (!stk.empty()) {
        next_e[i] = stk.back();
      }
      stk.push_back(i);
    }
    vector<int64_t> ans(n + 1);
    for (int i = 0; i < n; i++) {
      if (next_e[i] < n && a[next_e[i]] == a[i]) {
        int d = i - prev[i];
        ans[next_e[i]] += d;
        ans[min(next_e[next_e[i]], next[i])] -= d;
      }
    }
    for (int i = 0; i < n; i++) {
      ans[i + 1] += ans[i];
    }
    for (int i = 0; i < n; i++) {
      ans[i + 1] += ans[i];
    }
    int q;
    cin >> q;
    while (q--) {
      int k;
      cin >> k;
      cout << ans[n - k - 1] << '\n';
    }
  }
  return 0;
}
