#include <bits/stdc++.h>
using namespace std;

namespace std {

template <class Fun> class y_combinator_result {
	Fun fun_;

  public:
	template <class T>
	explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

	template <class... Args> decltype(auto) operator()(Args &&...args) {
		return fun_(std::ref(*this), std::forward<Args>(args)...);
	}
};

template <class Fun> decltype(auto) y_combinator(Fun &&fun) {
	return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

}  // namespace std

class WaveletTree {
	int n;
	vector<long long> vmap;
	vector<vector<int>> tree;
	vector<vector<long long>> psum;

	template <typename I> void build(I begin, I end, int t, int vl, int vr) {
		if (vl == vr) {
			int nn = end - begin + 1;
			psum[t].reserve(nn);
			psum[t].push_back(0);
			for (auto it = begin; it != end; it++)
				psum[t].push_back(psum[t].back() + vmap[*it]);
			return;
		}
		int vm = (vl + vr) / 2, nn = end - begin + 1;
		tree[t].reserve(nn);
		psum[t].reserve(nn);
		tree[t].push_back(0);
		psum[t].push_back(0);
		for (auto it = begin; it != end; it++) {
			tree[t].push_back(tree[t].back() + (*it <= vm));
			psum[t].push_back(psum[t].back() + vmap[*it]);
		}
		auto pivot = stable_partition(begin, end, [vm](int x) { return x <= vm; });
		build(begin, pivot, t * 2, vl, vm);
		build(pivot, end, t * 2 + 1, vm + 1, vr);
	}

	long long query(int l, int r, int k, int t, int vl, int vr) {
		if (vl == vr) return k * vmap[vl];
		int vm = (vl + vr) / 2, lv = tree[t][r] - tree[t][l - 1];
		if (k <= lv) {
			return query(tree[t][l - 1] + 1, tree[t][r], k, t * 2, vl, vm);
		} else {
			return psum[t * 2][tree[t][r]] - psum[t * 2][tree[t][l - 1]] +
			       query(l - tree[t][l - 1], r - tree[t][r], k - lv, t * 2 + 1, vm + 1,
			             vr);
		}
	}

  public:
	WaveletTree(vector<long long> vec) { init(vec.begin(), vec.end()); }

	// resets data structure to inital state
	template <typename I> void init(I begin, I end) {
		map<long long, int> m;
		for (auto it = begin; it != end; it++) m[*it] = 0;
		n = 0;
		vmap.resize(m.size());
		for (auto &[k, v] : m) vmap[v = n++] = k;
		for (auto it = begin; it != end; it++) *it = m[*it];
		tree.resize(4 * n);
		psum.resize(4 * n);
		build(begin, end, 1, 0, n);
	}

	// returns sum of k smallest elements in range [l, r]
	long long query(int l, int r, int k) {
		assert(k <= r - l + 1);
		return query(l + 1, r + 1, k, 1, 0, n);
	}
};

int main() {
	int N, M;
	cin >> N >> M;
	vector<pair<long long, long long>> A(N);
	for (auto &[v, c] : A) {
		cin >> v >> c;
		v = -v;
	}
	sort(A.begin(), A.end(), [](auto a, auto b) { return a.second < b.second; });

	vector<long long> V(N), C(N);
	for (int i = 0; i < N; i++) { tie(V[i], C[i]) = A[i]; }

	WaveletTree wt(V);
	vector<int> rpos(N - M + 1);

	y_combinator([&](auto self, int pl, int pr, int ql, int qr) -> void {
		if (pr < pl) { return; }
		if (ql == qr) {
			for (int i = pl; i <= pr; i++) rpos[i] = ql;
			return;
		}
		int pm = (pl + pr) / 2, qm = -1;
		long long val = LLONG_MIN;
		for (int i = ql; i <= qr; i++) {
			if (i - pm + 1 < M) { continue; }
			long long cur = -wt.query(pm, i, M) - 2 * (C[i] - C[pm]);
			if (val < cur) {
				val = cur;
				qm = i;
			}
		}
		rpos[pm] = qm;
		self(pl, pm - 1, ql, qm);
		self(pm + 1, pr, qm, qr);
	})(0, N - M, M - 1, N - 1);

	long long ans = LLONG_MIN;
	for (int l = 0; l < N - M + 1; l++) {
		int r = rpos[l];
		ans = max(ans, -wt.query(l, r, M) - 2 * (C[r] - C[l]));
	}
	cout << ans << endl;
}
