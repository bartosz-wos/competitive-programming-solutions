#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
static ll fact[1000001], inv[1000001];
int occur[26];
string a;
 
ll exp(ll a, ll w) {
	ll ans = 1;
	a %= mod;
	while(w) {
		if(w & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		w >>= 1;
	}
	return ans;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	fact[0] = 1;
	inv[0] = 1;
	for(int i = 1; i <= 1e6; ++i)
		fact[i] = fact[i-1] * i % mod;
	inv[1000000]=exp(fact[1000000],mod-2);
	for(int i=1000000-1;i>=1;--i)
		inv[i]=(1LL*i+1LL)*inv[i+1]%mod;
	cin >> a;
	int sum = 0;
	for(const char& i : a)
		++occur[i - 97], ++sum;
 
	ll result = fact[sum];
 
	for(int i = 0; i < 26; ++i)
		result = (result * inv[occur[i]]) % mod;
 
	cout << result;
}
