#include<iostream>
using namespace std;
constexpr int mod = 1e9 + 7;
#define ios ios::sync_with_stdio(false);
using ull = unsigned long long;
 
ull fact[2000007], inv[2000007];
ull exp(ull a, ull w) {
	ull ans = 1;
	a = a%mod;
	while(w) {
		if(w & 1)
			ans = ans * a % mod;
		a = a * a % mod;
		w >>= 1;
	}
	return ans;
}
 
ull a, b;
int main() {
	ios;
	cin >> a >> b;
	fact[0] = 1;
	inv[0] = 1;
	for(int i = 1; i <= 2000000; ++i) {
		fact[i] = fact[i - 1] * i % mod;
		inv[i] = exp(fact[i], mod-2);
	}
 
	cout << fact[a+b-1]*inv[a-1]%mod*inv[b]%mod;
}
