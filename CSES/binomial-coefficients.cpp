#include<iostream>
using namespace std;
using ll = long long;
constexpr int MOD = 1000000007;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
ll fact[1000007], inv[1000007];
 
ll pot(ll a, ll w) {
	ll ans = 1;
	while (w) {
		if (w & 1)
			ans = (ans * a) % MOD;
		a = (a * a) % MOD;
		w >>= 1;
	}
	return ans;
}
 
ll n, a, b;
int main() {
	ios;
	fact[0] = 1;
	inv[0] = 1;
	for (int i = 1; i <= 1000001; ++i) {
		fact[i] = (fact[i - 1] * i) % MOD;
		inv[i] = pot(fact[i], MOD - 2);
	}
 
	cin >> n;
	while (n--) {
		cin >> a >> b;
		cout << fact[a] * inv[b] % MOD * inv[a - b] % MOD << '\n';
	}
}
