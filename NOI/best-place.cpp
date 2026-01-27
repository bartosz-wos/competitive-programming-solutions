#include "bits/stdc++.h"

using namespace std;

#define ln "\n"
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define int long long
const int MOD = 1e9 + 7;
const int inf = 2e18;
vector<int> x, y;
int n;

signed main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        int a, b; cin >> a >> b;
        x.pb(a);
        y.pb(b);
    }
    sort(all(x));
    sort(all(y));
    if(n % 2 == 1) {
        cout << x[n / 2] << ' ' << y[n / 2];
    } else {
        int X = (x[n / 2] + x[n / 2 - 1]) / 2; 
        int Y = (y[n / 2] + y[n / 2 - 1]) / 2;
        cout << X << ' ' << Y << ln;
    }
}   
