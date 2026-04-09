#include <iostream>
#include <algorithm>
using namespace std;
using ull = unsigned long long;
constexpr int MOD = 1000000007;
 
 
ull quickpow(ull a, ull w) {
	ull ans = 1;
 
	while (w) {
		if (w & 1)
			ans = (ans * a) % MOD;
		a = (a * a) % MOD;
		w >>= 1;
	}
	return ans;
}
 
int q, a, b;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> q;
	while (q--) {
		cin >> a >> b;
		cout << quickpow(a, b) << '\n';
	}
}
