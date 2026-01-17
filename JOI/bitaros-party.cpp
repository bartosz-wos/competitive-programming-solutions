#include <bits/stdc++.h>
using namespace std;
constexpr int SQ = 150;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<int>> rg(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		rg[--v].push_back(--u);
	}

	vector<vector<pair<int, int>>> path_sizes(n);
	vector<int> from(n, -1);

	for (int i = 0; i < n; i++) {
		path_sizes[i].push_back({0, i});
		vector<int> from_indicies;

		for (int j : rg[i]) {
			for (auto [dist, idx] : path_sizes[j]) {
				if (from[idx] == -1) {
					from_indicies.push_back(idx);
					from[idx] = dist + 1;
				} else {
					from[idx] = max(from[idx], dist + 1);
				}
			}
		}

		for (int j : from_indicies) { path_sizes[i].push_back({from[j], j}); }
		sort(path_sizes[i].rbegin(), path_sizes[i].rend());
		while (path_sizes[i].size() > SQ) { path_sizes[i].pop_back(); }

		for (int j : from_indicies) { from[j] = -1; }
	}

	vector<bool> blocked(n);
	for (int query = 0; query < q; query++) {
		int t, y;
		cin >> t >> y;
		t--;

		vector<int> c(y);
		for (int i = 0; i < y; i++) {
			cin >> c[i];
			blocked[--c[i]] = true;
		}

		int ans = -1;
		if (y >= SQ) {
			vector<int> dp(t + 1, -1);
			dp[t] = 0;
			for (int i = t; i >= 0; i--) {
				if (dp[i] == -1) { continue; }
				if (!blocked[i]) { ans = max(ans, dp[i]); }
				for (int j : rg[i]) { dp[j] = max(dp[j], dp[i] + 1); }
			}
		} else {
			for (auto [dist, idx] : path_sizes[t]) {
				if (!blocked[idx]) {
					ans = dist;
					break;
				}
			}
		}

		cout << ans << "\n";

		for (int i : c) { blocked[i] = false; }
	}
}
