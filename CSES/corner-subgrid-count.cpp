#include<bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
using ll = long long;
constexpr int maxn = 3001;
 
int n;
ll ans;
bitset<maxn> T[maxn];
 
ll f(int a) {
	return a * (a - 1);
}
 
void solve() {
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> T[i];
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			ans += f( (T[i] & T[j]).count() );
	cout << ans / 2;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t = 1;
	while(t--)
		solve();
}
