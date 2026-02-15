#include <bits/stdc++.h>
using namespace std;

const int mxn = 2e5 + 10;
int root[mxn], tree[mxn * 40];
int lc[mxn * 40], rc[mxn * 40];
int a[mxn], rev[mxn], TIME;

int upt(int tl, int tr, int par, int pos, int add) {
	int cur = ++TIME;
	if(tl == tr) {
		tree[cur] = tree[par] + add;
		return cur;
	}

	int tm = (tl + tr) / 2;
	if(pos <= tm) {
		lc[cur] = upt(tl, tm, lc[par], pos, add);
		rc[cur] = rc[par];
	} else {
		lc[cur] = lc[par];
		rc[cur] = upt(tm + 1, tr, rc[par], pos, add);
	}

	tree[cur] = tree[lc[cur]] + tree[rc[cur]];
	return cur;
}

int query(int tl, int tr, int L, int R, int k) {
	if(tl == tr) return tl;
	int tm = (tl + tr) / 2;
	int cnt_lc = tree[lc[R]] - tree[lc[L]];
	if(cnt_lc < k) {
		return query(tm + 1, tr, rc[L], rc[R], k - cnt_lc);
	} else {
		return query(tl, tm, lc[L], lc[R], k);
	}
	return 69;
}

int main() {
	int n, q;
	cin >> n >> q;

	map<int, int> mp;
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		mp[a[i]];
	}

	int N = 0;
	for(auto &p : mp) {
		p.second = ++N;
		rev[p.second] = p.first;
	}

	for(int i = 1; i <= n; i++) {
		a[i] = mp[a[i]];
		root[i] = upt(1, N, root[i - 1], a[i], 1);
	}

	while(q--) {
		int l, r, k;
		cin >> l >> r >> k;
		cout << rev[query(1, N, root[l], root[r], k + 1)] << endl;
	}
	return 0;
}
