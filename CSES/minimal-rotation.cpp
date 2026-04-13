#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9+7;
constexpr int P = 37;
ll inv[2000001];
ll HASH[2000001];
 
int exp(ll a, ll w) {
	ll ans = 1;
	while(w) {
		if(w & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		w >>= 1;
	}
	return ans;
}
 
int get(int l, int r) {
	return ( HASH[r] - HASH[l-1] + mod ) % mod * inv[l-1] % mod;
}
 
string s;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> s;
	s += s;
	int n = s.size();
	ll pot = 1;
	inv[0] = 1;
	for(int i = 1; i <= n; ++i) {
		HASH[i] = ( HASH[i-1] + ( (s[i-1] - 96) * pot % mod ) ) % mod;
		pot = pot * P % mod;
		inv[i] = exp(pot, mod - 2);
	}
	n >>= 1;
	int k = 1;
	for(int i = 2; i <= n; ++i) {
		int lo = 0, hi = n - 1;
		while(lo <= hi) {
			int mid = (lo + hi) >> 1;
			if(get(i, i + mid) == get(k, k + mid))
				lo = mid + 1;
			else
				hi = mid - 1;
		}
		if(lo <= n - 1 && s[i + lo - 1] < s[k + lo - 1])
			k = i;
	}
	for(int i = k - 1; i < k - 1 + n; ++i)
		cout << s[i];
}
