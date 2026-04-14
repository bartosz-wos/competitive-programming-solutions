#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9+7;
constexpr int P = 37;
int n, q;
static ll pot[200007];
static ll inv[200007];
 
ll exp(ll a, ll w) {
	ll ans = 1;
	while(w) {
		if(w & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		w >>= 1;
	}
	return ans;
}
 
struct BIT {
	ll bit[200007];
 
	void upd(int i, int x) {
		for(; i <= 200002; i += i & -i)
			bit[i] = (bit[i] + x) % mod;
	}
 
	ll query(int a, int b) {
		ll ans = 0;
		for(; b; b -= b & -b)
			ans = (ans + bit[b]) % mod;
		--a;
		for(; a; a -= a & -a)
			ans = (ans - bit[a] + mod) % mod;
		return ans;
	}
} pref, suf;
 
string s;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	pot[0] = 1;
	inv[0] = 1;
	cin >> n >> q;
	cin >> s;
	for(int i = 1; i <= n; ++i) {
		pot[i] = pot[i-1] * P % mod;
		inv[i] = exp(pot[i], mod - 2);
	}
	for(int i = 1; i <= n; ++i)
		pref.upd(i, (s[i-1] - 96) * pot[i-1] % mod);
	for(int i = 1; i <= n; ++i)
		suf.upd(i, (s[n-i]-96) * pot[i-1] % mod);
 
	while(q--) {
		int z;
		cin >> z;
		if(z == 1) {
			int a;
			char b;
			cin >> a >> b;
			ll bp = (b - 96) * pot[a-1] % mod;
			ll bs = (b - 96) * pot[n - a] % mod;
			ll kp = pref.query(a, a);
			ll ks = suf.query(n - a + 1, n - a + 1);
			pref.upd(a, bp - kp);
			suf.upd(n - a + 1, bs - ks);
		}
		else {
			int a, b;
			cin >> a >> b;
			cout << ( pref.query(a, b) * inv[a-1] % mod == suf.query(n - b + 1, n - a + 1) * inv[n - b] % mod ? "YES\n" : "NO\n");
		}
	}
}
