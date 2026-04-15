#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
ll x[1002], y[1002], ans;
 
void solve() {
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];
	x[n] = x[0];
	y[n] = y[0];
 
	for(int i = 0; i < n; ++i)
		ans += ( x[i] * y[i+1] - y[i] * x[i+1] );
	cout << abs(ans);
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t = 1;
	while(t--)
		solve();
}
