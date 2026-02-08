#include<bits/stdc++.h>

using namespace std;
using ll = long long;
const ll N = 1e5 + 2;
pair < ll, ll > P[N];
int main() {
	ll n, m, r, lo, mid, hi, x, y, i, j, s, mn, ans, t, mx, can = 0;

	cin >> n >> m;
	
	for (i = 1; i <= n; i ++) {
		cin >> P[i].second >> P[i].first;
	}
	ll b[m + 2], a[n + 2];
	for (i = 1; i <= m; i ++) {
		cin >> b[i];
	}
	sort ( b + 1, b + m + 1);
	sort ( P + 1, P + n + 1);
	
	for (i = 1; i <= n; i ++) a[i] = P[i].second;
	vector < ll > v;
	j = n;
	for (i = m; i >= 1; i --) {
		while ( j >= 1 && a[j] > b[i]) j --;
		if ( j== 0) break;
		j --;
	}
	
	cout<< m - i<< endl;
	
	
	
	
}

