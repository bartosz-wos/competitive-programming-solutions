#include "Bob.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll Bob(vector<pair<int, int>> edg) {
	const int kN = 5000;
	const __uint128_t kX = 1e18;
	array<bool, kN + 1> sieve;
	fill(sieve.begin(), sieve.end(), true);
	sieve[0] = sieve[1] = false;
	for(int i = 4; i <= kN; i += 2) {
		sieve[i] = false;
	}
	for(int i = 3; i * i <= kN; i += 2) {
		if(sieve[i]) {
			for(int j = i * i; j <= kN; j += 2 * i) {
				sieve[j] = false;
			}
		}
	}
	__uint128_t p = 1;
	vector<pair<int, int>> cong;
	for(const auto &[a, m] : edg) {
		if(sieve[m - 1]) {
			cong.emplace_back(a - 1, m - 1);
			p = p * (m - 1);
		}
		if(p > kX) {
			break;
		}
	}
	auto inv = [&](__uint128_t a, int m) -> __uint128_t {
		a %= m;
		int b = m - 2;
		__uint128_t res = 1;
		while(b) {
			if(b & 1) {
				res = res * a % m;
			}
			a = a * a % m;
			b >>= 1;
		}
		return res;
	};
	__uint128_t res = 0;
	for(const auto &[a, m] : cong) {
		__uint128_t aux = p / m, n = inv(aux, m);
		assert(n * aux % m == 1);
		res = (res + a * aux % p * n) % p;
	}
	return (ll)res;
}

