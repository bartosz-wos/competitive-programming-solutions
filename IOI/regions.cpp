#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, r, q;
	cin >> n >> r >> q;
	vector<int> region(n);
	cin >> region[0];
	region[0]--;
	vector<vector<int>> adj(n);
	for (int i = 1; i < n; i++) {
		int p, h;
		cin >> p >> h;
		p--, h--;
		adj[p].push_back(i);
		region[i] = h;
	}
	vector<int> tin(n);
	vector<int> tout(n);
	vector<int> tin_node(n);
	vector<vector<int>> comp(r);
	int timer = 0;
	function<void(int)> tour = [&](int u) -> void {
		tin[u] = timer++;
		tin_node[tin[u]] = u;
		comp[region[u]].push_back(tin[u]);
		for (int v : adj[u]) { tour(v); }
		tout[u] = timer;
	};
	tour(0);

	const int BLOCK = sqrt(n);
	vector<vector<int>> calc;
	vector<int> region_id(r, -1);
	function<void(int, int, int)> dfs = [&](int u, int parent_region,
	                                        int parent_count) -> void {
		if (region[u] == parent_region) { parent_count++; }
		calc[region_id[parent_region]][region[u]] += parent_count;
		for (int v : adj[u]) { dfs(v, parent_region, parent_count); }
	};

	int current_id = 0;
	for (int i = 0; i < r; i++) {
		if ((int)comp[i].size() >= BLOCK) {
			region_id[i] = current_id++;
			calc.push_back(vector<int>(r));
			dfs(0, i, 0);
		}
	}

	for (int i = 0; i < q; i++) {
		int e1, e2;
		cin >> e1 >> e2;
		e1--, e2--;
		if ((int)comp[e1].size() >= BLOCK) {
			cout << calc[region_id[e1]][e2] << "\n";
		} else {
			int total = 0;
			for (int u : comp[e1]) {
				total +=
				    lower_bound(begin(comp[e2]), end(comp[e2]), tout[tin_node[u]]) -
				    lower_bound(begin(comp[e2]), end(comp[e2]), tin[tin_node[u]]);
			}
			cout << total << '\n';
		}
	}
}
