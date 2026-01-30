#include<bits/stdc++.h>

using namespace std;
using ll = long long;
map < ll , ll > X, Y;
ll x[300005], y[300005];
int main() {
	ll n, m, r, i, j, ans, t;

	cin >> n;
	
	for (i= 1; i<= n; i ++) {
		cin >> x[i] >> y[i];
		X[x[i]] ++;
		Y[y[i]] ++;
	}
	ans =0;
	for (i = 1; i <= n; i ++) {
		r = (X[x[i]] - 1) * (Y[y[i]] - 1);
		ans += r;
	}
	cout << ans << endl;
}
