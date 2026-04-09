#include<iostream>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
 
ll exp(ll a, ll w, ll p) {
	ll ans = 1;
	a %= p;
 
	while (w) {
		if (w & 1)
			ans = ans * a % p;
		a = a * a % p;
		w >>= 1;
	}
	return ans;
}
 
ll n, a, b, c;
int main() {
	cin >> n;
	while (n--) {
		cin >> a >> b >> c;
		cout << exp(a, exp(b, c, mod - 1), mod) << '\n';
	}
}
