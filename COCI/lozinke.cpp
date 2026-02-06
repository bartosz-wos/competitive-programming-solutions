#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int n, ans = 0;
  cin >> n;
  vector<string> ps(n);
  map<string, int> cnt;
  for (string& p : ps) {
    cin >> p;
    set<string> ss;
    for (int i = 0, len = p.length(); i < len; i++)
      for (int j = 1; j <= len - i; j++) ss.insert(p.substr(i, j));
    for (const string& s : ss) ++cnt[s];
  }
  for (const string& p : ps) ans += cnt[p] - 1;
  cout << ans << "\n";
  return 0;
}
