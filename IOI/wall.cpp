#include <bits/stdc++.h>
using namespace std;

struct Update {
	int min_val = 0;
	int max_val = INT_MAX;
};
class Segtree {
	const int sz;
	vector<Update> t;

	void apply(int v, const Update &x) {
		t[v].min_val = max(t[v].min_val, x.min_val);
		t[v].max_val = max(t[v].max_val, t[v].min_val);
		t[v].max_val = min(t[v].max_val, x.max_val);
		t[v].min_val = min(t[v].min_val, t[v].max_val);
	}

	void push_down(int v) {
		apply(2 * v, t[v]);
		apply(2 * v + 1, t[v]);
		t[v] = Update();
	}

	void update(int v, int l, int r, int ql, int qr, const Update &x) {
		if (qr < l || ql > r) { return; }
		if (ql <= l && r <= qr) {
			apply(v, x);
		} else {
			push_down(v);
			int m = (l + r) / 2;
			update(2 * v, l, m, ql, qr, x);
			update(2 * v + 1, m + 1, r, ql, qr, x);
		}
	}

	Update query(int v, int l, int r, int idx) {
		if (l == r) {
			return t[v];
		} else {
			push_down(v);
			int m = (l + r) / 2;
			return (idx <= m) ? query(2 * v, l, m, idx)
			                  : query(2 * v + 1, m + 1, r, idx);
		}
	}

  public:
	Segtree(int n) : sz(n), t(4 * n) {}

	void update(int ql, int qr, const Update &x) { update(1, 0, sz - 1, ql, qr, x); }

	Update get(int idx) { return query(1, 0, sz - 1, idx); }
};

void buildWall(int n, int k, int op[], int left[], int right[], int height[],
               int final_height[]) {
	Segtree st(n);
	for (int i = 0; i < k; i++) {
		if (op[i] == 1) {
			st.update(left[i], right[i], {height[i], INT_MAX});
		} else {
			st.update(left[i], right[i], {0, height[i]});
		}
	}
	for (int i = 0; i < n; i++) { final_height[i] = st.get(i).min_val; }
}
