#include <bits/stdc++.h>
#define F first
#define S second
#define LL long long
 
#define rep(i, x) for(auto &i : (x))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
 
#define left(x) ((x)<<1)
#define right(x) ((x)>>1)
#define LSOne(x) (x & -(x))
 
using namespace std;
using T = pair<pair<int, int>, int>;
 
const int SZ = 2e5 + 1;
const LL MOD = 1e9 + 7; 
const LL INF = 1e18 + 1;
 
LL bp (LL b, LL e, LL m = MOD) {
 if ( e == 0 ) return 1;
 LL T = bp(b, e / 2);
 T *= T; T %= m;
 if ( e & 1 ) T *= b;
 return T %= m;
}
 
LL nv_i (LL a) { return bp(a, MOD - 2); };
LL gcd (LL a, LL b) { return (b == 0 ? a : gcd(b, a % b)); }
LL lcm(LL a, LL b) { return (a * (b / gcd(a, b))); }
LL ceil (LL a, LL b) { return ((a + b - 1) / b); }
 
void solve() {
  int n;
  cin >> n;

  vector<int> BOXES(n), WANDS(n);

  rep(i, WANDS) cin >> i;
  rep(i, BOXES) cin >> i;

  sort(all(WANDS));
  sort(all(BOXES));

  for(int i = 0; i < n; i ++) {
    if(WANDS[i] > BOXES[i]) {
      cout << "NE";
      return;
    }
  }

  cout << "DA";
}
 
signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
 
  solve();
  return 0;
}
