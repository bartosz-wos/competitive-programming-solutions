#include<bits/stdc++.h>

using namespace::std;



const int ROOTS = 1000000 + 5;

const int N = 100000 + 5;

const int LOG = 21;

const int NODES = 2 * N * (1 + 7 * LOG);



int n;

int q;

int a[N];

int nodes;

int pf[ROOTS];

int root[ROOTS];

int L[NODES];

int R[NODES];

int sorted[N];

int sum[NODES];

vector<int> primes;

bitset<ROOTS> composite;

vector<pair<int, int>> pos[ROOTS];



int add_node(int prv = -1) {

	L[nodes] = R[nodes] = -1;

	if(~prv) sum[nodes] = sum[prv];

	return nodes++;

}



void build(int pos, int l = 1, int r = n) {

	if(l == r) {

		return;

	}

	int mi = (l + r) / 2;

	L[pos] = add_node();

	R[pos] = add_node();

	build(L[pos], l, mi);

	build(R[pos], mi + 1, r);

	sum[pos] = sum[L[pos]] + sum[R[pos]];

}



void update(int x, int y, int last, int pos, int l = 1, int r = n) {

	if(l == r) {

		sum[pos] += y;

		return;

	}

	int mi = (l + r) / 2;

	if(x <= mi) {

		L[pos] = add_node(L[last]);

		R[pos] = R[last];

		update(x, y, L[last], L[pos], l, mi);

	}

	else {

		L[pos] = L[last];

		R[pos] = add_node(R[last]);

		update(x, y, R[last], R[pos], mi + 1, r);

	}

	sum[pos] = sum[L[pos]] + sum[R[pos]];

}



long long query(int x, int y, int pos, int l = 1, int r = n) {

	if(y < l or r < x or x > y) return 0;

	if(x <= l and r <= y) return sum[pos];

	int mi = (l + r) / 2;

	return query(x, y, L[pos], l, mi) + query(x, y, R[pos], mi + 1, r);

}



void init() {

	composite[1] = 1;

	for(int i = 2; i < ROOTS; i++) {

		if(!composite[i]) {

			pf[i] = i;

			primes.emplace_back(i);

		}

		for(int p : primes) {

			if(i * p >= ROOTS) break;

			composite[i * p] = 1;

			pf[i * p] = p;

			if(i % p == 0) break;

		}

	}

	for(int i = 1; i <= n; i++) {

		int x = a[i];

		while(x != 1) {

			int f = pf[x];

			int e = 0;

			while(x % f == 0) {

				x /= f;

				e += 1;

			}

			pos[f].emplace_back(i, e);

		}

	}

	root[0] = add_node();

	build(root[0]);

	for(int i = 1; i < ROOTS; i++) {

		root[i] = root[i - 1];

		for(auto x : pos[i]) {

			int p, e;

			tie(p, e) = x;

			int new_rt = add_node();

			update(p, e, root[i], new_rt);

			root[i] = new_rt;

		}

	}

}



int solve(int l, int r, int x, int y) {

	return query(l, r, root[y]) - query(l, r, root[x - 1]);

}



int main() {

	cin.tie(0) -> sync_with_stdio(false);

	cin >> n;

	for(int i = 1; i <= n; i++) cin >> a[i];

	init();

	cin >> q;

	while(q--) {

		int l, r, x, y;

		cin >> l >> r >> x >> y;

		cout << solve(l, r, x, y) << '\n';

	}
}
