#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 998244353;

ll bin_exp(ll x, ll n) {
	assert(n >= 0);

	x %= MOD;

	ll res = 1;
	while (n > 0) {
		if (n % 2 == 1) { res = res * x % MOD; }
		x = x * x % MOD;
		n /= 2;
	}
	return res;
}

int main() {
	int q;
	cin >> q;

	ll mult_x = 1;
	ll constant = 0;
	queue<pair<int, int>> f;
	for (int i = 0; i < q; i++) {
		int type;
		cin >> type;

		if (type == 0) {
			int a, b;
			cin >> a >> b;

			f.push({a, b});

			mult_x = (mult_x * a) % MOD;

			constant = ((constant * a) % MOD + b) % MOD;
		} else if (type == 1) {
			pair<int, int> x = f.front();
			f.pop();

			ll inv = bin_exp(x.first, MOD - 2);

			mult_x = (mult_x * inv) % MOD;
			constant -= (x.second * mult_x) % MOD;

			if (constant < 0) { constant += MOD; }
		} else if (type == 2) {
			int x;
			cin >> x;

			cout << ((mult_x * x) + constant) % MOD << endl;
		}
	}
}
