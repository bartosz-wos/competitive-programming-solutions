#include <bits/stdc++.h>

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	struct graph_t {
		std::vector<int> dfn, siz;
		std::vector<std::vector<int>> adj;
		int tot;
		graph_t (int n) {
			dfn = std::vector<int>(n, 0);
			siz = std::vector<int>(n, 1);
			adj = std::vector(n, std::vector<int>());
			for (int i = 1; i < n; ++i) {
				int fa;
				std::cin >> fa;
				--fa;
				adj[fa].emplace_back(i);
			}
			tot = 0;
			auto dfs = [&](auto &self, int x) -> void {
				dfn[x] = tot++;
				for (int y : adj[x]) {
					self(self, y);
					siz[x] += siz[y];
				}
			};
			dfs(dfs, 0);
		}
	} F(n), G(n);
	struct query_t {
		int id, x, y, coef;
		query_t(int id, int x, int y, int coef) : id(id), x(x), y(y), coef(coef) {

		}
		bool operator<(const query_t &rhs) const {
			return x < rhs.x;
		}
	};
	struct fenwick_t {
		std::vector<int> t;
		static constexpr int lowbit(int x) { return x & -x; }
		void add(int p, int v) {
			++p;
			for (; p < t.size(); p += lowbit(p))
				t[p] += v;
		}
		int query(int p) {
			++p;
			int r = 0;
			for (; p; p -= lowbit(p))
				r += t[p];
			return r;
		}
		fenwick_t(int n) {
			t = std::vector<int>(n + 1, 0);
		}
	} tr(n);
	std::vector<std::pair<int, int>> points;
	for (int i = 0; i < n; ++i) {
		points.emplace_back(F.dfn[i], G.dfn[i]);
	}
	std::sort(points.begin(), points.end());
	std::vector<int> ans(n);
	std::vector<query_t> queries;
	auto add_query = [&](int id, int r1, int r2, int sgn) {
		if (r1 < 0 || r2 < 0) return;
		queries.emplace_back(id, r1, r2, sgn);
	};
	for (int i = 0; i < n; ++i) {
		int l1 = F.dfn[i], r1 = F.dfn[i] + F.siz[i] - 1;
		int l2 = G.dfn[i], r2 = G.dfn[i] + G.siz[i] - 1;
		add_query(i, r1, r2, 1);
		add_query(i, l1 - 1, r2, -1);
		add_query(i, r1, l2 - 1, -1);
		add_query(i, l1 - 1, l2 - 1, 1);
	}
	std::sort(queries.begin(), queries.end());
	int p = 0;
	for (auto [id, l, r, coef] : queries) {
		while (p < points.size() && points[p].first <= l) {
			tr.add(points[p].second, 1);
			++p;

		}
		ans[id] += coef * tr.query(r);
	}
	for (int i = 0; i < n; ++i) {
		std::cout << ans[i] - 1 << ' ';
	}
	std::cout << '\n';
}
