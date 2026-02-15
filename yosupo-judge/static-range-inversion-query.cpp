#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using P = pair<int, int>;
const int N = 1e5 + 1;
const int S = 300;

template <class T> class BIT {
  private:
	int size;
	vector<T> bit;
	vector<T> arr;

  public:
	BIT(int size) : size(size), bit(size + 1), arr(size) {}

	void set(int ind, T val) { add(ind, val - arr[ind]); }
	
	void add(int ind, T val) {
		arr[ind] += val;
		ind++;
		for (; ind <= size; ind += ind & -ind) { bit[ind] += val; }
	}

	
	T pref_sum(int ind) {
		ind++;
		T total = 0;
		for (; ind > 0; ind -= ind & -ind) { total += bit[ind]; }
		return total;
	}
};


struct Query {
	int l, r, i;
};

int main() {
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	for (int i = 0; i < n; i++) { cin >> a[i]; }
	vector<int> b(a);
	sort(b.begin(), b.end());
	b.erase(unique(b.begin(), b.end()), b.end());

	auto id = [&](int x) {
		return lower_bound(b.begin(), b.end(), a[x]) - b.begin();
	};

	vector<Query> q(k);
	for (int i = 0; i < k; i++) {
		q[i].i = i;
		cin >> q[i].l >> q[i].r;
	}
	q.push_back({0, 0, -1});  // add dummy initial query
	sort(q.begin(), q.end(), [](Query x, Query y) {
		if (x.l / S != y.l / S) return x.l / S < y.l / S;
		else return x.r < y.r;
	});

	ll res = 0;
	BIT<int> bit(n);

	auto edit = [&](int id, int x, bool left) {
		res += (left ? bit.pref_sum(id - 1)
		             : bit.pref_sum(n - 1) - bit.pref_sum(id)) *
		       x;
		bit.add(id, x);
	};

	vector<ll> ans(k);
	for (int i = 0; i < q.size(); i++) {
		if (i) { ans[q[i].i] = res; }
		if (i + 1 >= q.size()) { break; }
		while (q[i].l > q[i + 1].l) { edit(id(--q[i].l), 1, true); }
		while (q[i].r < q[i + 1].r) { edit(id(q[i].r++), 1, false); }
		while (q[i].l < q[i + 1].l) { edit(id(q[i].l++), -1, true); }
		while (q[i].r > q[i + 1].r) { edit(id(--q[i].r), -1, false); }
	}

	for (int i = 0; i < k; i++) { cout << ans[i] << '\n'; }
}
