#include <bits/stdc++.h>
using namespace std;
#define sp << " " << 
#define int long long
#define vi vector<int>
#define F(xxx,yyy) for (int xxx=1;xxx<=yyy;xxx++)
#define pii pair<int,int>
const int N = 2e5+1;

void solve() {
  int n;
  cin >> n;
  vi a(n+1),l(n+1);
  F(i,n) cin >> a[i];
  int best = 2e18;
  for (int i=2;i<=n;i++) {
    if (abs(a[i]-a[i-1]) < best) {
      best = abs(a[i]-a[i-1]);
    }
  }
  cout << best << endl; 
}
    
                  
                             
signed main() { 
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  #ifdef Local
  freopen("in","r",stdin);
  freopen("out","w",stdout); 
  #endif
  int t = 1;
  //cin >> t;
	F(i,t) solve();
}
