#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

long long pow_mod(long long x, long long n, long long mod) {
	assert(n >= 0);
	x %= mod;
	long long res = 1;
	while (n > 0) {
		if (n % 2 == 1) { res = res * x % mod; }
		x = x * x % mod;
		n /= 2;
	}
	return res;
}

class HashedString {
  private:
	static const long long MOD = 1e9 + 9;
	static const long long POW = 101;

	static vector<long long> pow;
	static vector<long long> mod_inv;

	const string &s;
	vector<long long> p_hash;

  public:
	HashedString(const string &s) : s(s), p_hash(s.size() + 1) {
		while (pow.size() < s.size()) {
			pow.push_back((pow.back() * POW) % MOD);
			mod_inv.push_back(pow_mod(pow.back(), MOD - 2, MOD));
		}

		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = (p_hash[i] + s[i] * pow[i] % MOD) % MOD;
		}
	}

	long long hash(int from, int to) {
		long long pref = (p_hash[to + 1] - p_hash[from] + MOD) % MOD;
		return pref * mod_inv[from] % MOD;
	}

	long long hash(int from, int to, const pair<int, char> &rep) {
		long long pref = p_hash[to + 1] - p_hash[from];
		if (from <= rep.first && rep.first <= to) {
			pref += rep.second * pow[rep.first] - s[rep.first] * pow[rep.first];
		}
		return (pref % MOD + MOD) * mod_inv[from] % MOD;
	}
};
vector<long long> HashedString::pow = {1};
vector<long long> HashedString::mod_inv = {1};

int last_true(int lo, int hi, function<bool(int)> check) {
	int valid = -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		if (check(mid)) {
			lo = mid + 1;
			valid = mid;
		} else {
			hi = mid - 1;
		}
	}
	return valid;
}

vector<long long> range_res(int size, const vector<pair<int, int>> &ranges) {
	vector<long long> arr(size + 1);
	for (const auto &[a, b] : ranges) {
		arr[a]++;
		arr[b + 1]--;
	}
	for (int i = 1; i < size; i++) { arr[i] += arr[i - 1]; }
	for (const auto &[a, b] : ranges) { arr[b + 1] -= b - a + 1; }
	for (int i = 1; i < size; i++) { arr[i] += arr[i - 1]; }
	arr.pop_back();
	return arr;
}

int main() {
	string str;
	cin >> str;
	int len = str.size();

	string rev_str = str;
	reverse(rev_str.begin(), rev_str.end());
	HashedString h_str(str), h_rev_str(rev_str);
	auto is_pal = [&](int from, int to) {
		return h_str.hash(from, to) == h_rev_str.hash(len - to - 1, len - from - 1);
	};
	auto is_pal_rep = [&](int from, int to, pair<int, char> rep) {
		pair<int, char> r_rep{len - rep.first - 1, rep.second};
		return h_str.hash(from, to, rep) ==
		       h_rev_str.hash(len - to - 1, len - from - 1, r_rep);
	};

	function<bool(int)> check;
	vector<map<char, long long>> good(len);
	vector<pair<int, int>> removal1, removal2;
	long long init_amt = 0;
	for (int c = 0; c < len; c++) {
		int most = min(c, len - c - 1);  
		check = [&](int d) { return is_pal(c - d, c + d); };
		int raw_pal = last_true(0, most, check);
		init_amt += raw_pal + 1;
		if (raw_pal > 0) {
			removal1.push_back({c - raw_pal, c - 1});
			removal2.push_back({c + 1, c + raw_pal});
		}

		pair<int, char> rep = {c + raw_pal + 1, str[c - raw_pal - 1]};
		check = [&](int d) { return is_pal_rep(c - d, c + d, rep); };
		int rep_pal = last_true(raw_pal + 1, most, check);
		if (rep_pal != -1) {
			good[rep.first][rep.second] += rep_pal - raw_pal;
			good[c - raw_pal - 1][str[c + raw_pal + 1]] += rep_pal - raw_pal;
		}

		if (c < len - 1) {
			int most = min(c + 1, len - c - 1);
			check = [&](int d) { return is_pal(c - d + 1, c + d); };
			int raw_pal = last_true(0, most, check);
			init_amt += raw_pal;
			if (raw_pal > 0) {
				removal1.push_back({c - raw_pal + 1, c});
				removal2.push_back({c + 1, c + raw_pal});
			}

			pair<int, char> rep = {c + raw_pal + 1, str[c - raw_pal]};
			check = [&](int d) { return is_pal_rep(c - d + 1, c + d, rep); };
			int rep_pal = last_true(raw_pal + 1, most, check);
			if (rep_pal != -1) {
				good[rep.first][rep.second] += rep_pal - raw_pal;
				good[c - raw_pal][str[c + raw_pal + 1]] += rep_pal - raw_pal;
			}
		}
	}

	for (pair<int, int> &r : removal2) { r = {len - r.second - 1, len - r.first - 1}; }
	vector<long long> bad1 = range_res(len, removal1);
	vector<long long> bad2 = range_res(len, removal2);
	std::reverse(bad2.begin(), bad2.end());

	long long max_weight = init_amt;
	for (int i = 0; i < len; i++) {
		long long max_inc = 0;
		for (const auto &[_, i] : good[i]) { max_inc = max(max_inc, i); }
		max_weight = max(max_weight, init_amt + max_inc - bad1[i] - bad2[i]);
	}

	cout << max_weight << endl;
}
