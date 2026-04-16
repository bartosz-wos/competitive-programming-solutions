#include<iostream>
#include<string>
#include<cstring>
#include<algorithm>
#include<array>
#include<climits>
#include<vector>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
#include<chrono>
using namespace std;
using ll = long long;
using ar2 = array<ll, 2>;
using ar3 = array<ll, 3>;
using ar4 = array<ll, 4>;
#define rep(i, s, e) for(int i = s; i <= e; ++i)
constexpr ll inf = 1LL << 60;
constexpr int mod = 1e9 + 7;
constexpr int poz = 20;
constexpr int u = 1 << (poz - 1);
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
ll n, x;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> x;
	vector<int> tab(n);
	for (int& i : tab)
		cin >> i;
 
	auto get_sums = [&](int l, int r) -> vector<ll> {
		int len = r - l + 1;
		vector<ll> res;
 
		for (int mask = 0; mask < (1 << len); ++mask) {
			ll sum = 0;
			for (int j = 0; j < len; ++j)
				if (mask & (1 << j))
					sum += tab[l + j];
			res.push_back(sum);
		}
		return res;
	};
 
	vector<ll> left = get_sums(0, n / 2 - 1);
	vector<ll> right = get_sums(n / 2, n - 1);
	sort(left.begin(), left.end());
	sort(right.begin(), right.end());
 
	ll ans = 0;
	for (const ll& i : left) {
		auto low = lower_bound(right.begin(), right.end(), x - i);
		auto hi = upper_bound(right.begin(), right.end(), x - i);
		int start = low - right.begin();
		int end = hi - right.begin();
		ans += end - start;
	}
	cout << ans;
}
