#include <bits/stdc++.h>
using namespace std;

multiset<pair<int, int>> graph[60001];
bool visited[60001];
bitset<600001> possible;
int tot = 0, sm = 0;

void dfs(int node) {
	visited[node] = true;
	if (!graph[node].size()) return;
	int nxt, cost;
	tie(nxt, cost) = *graph[node].begin();

	tot += cost;
	if (!visited[nxt]) {
		graph[nxt].erase(graph[nxt].find({node, -cost}));
		graph[node].clear();
		dfs(nxt);
	}
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= 2 * n; i++) {
		int l, r, s;
		scanf("%d %d %d", &l, &r, &s);
		graph[l].insert({n + r, s});
		graph[n + r].insert({l, -s});
	}

	queue<int> q;
	for (int i = 1; i <= 2 * n; i++) {
		if (graph[i].size() == 1) q.push(i);
		if (graph[i].size() == 0) return printf("NO\n"), 0;
	}
	while (q.size()) {
		int curr = q.front();
		q.pop();
		if (graph[curr].size() == 0) return printf("NO\n"), 0;
		int nxt, cost;
		tie(nxt, cost) = *graph[curr].begin();
		tot += cost;

		graph[curr].clear();
		graph[nxt].erase(graph[nxt].find({curr, -cost}));
		if (graph[nxt].size() == 1) q.push(nxt);
	}

	vector<int> items;
	if (tot) items.push_back(abs(tot));
	for (int i = 1; i <= 2 * n; i++)
		if (!visited[i] && graph[i].size()) {
			tot = 0;
			graph[i].erase(graph[i].begin());
			dfs(i);
			if (tot) items.push_back(abs(tot));
		}
	sm = accumulate(items.begin(), items.end(), 0);

	possible[0] = 1;
	for (int i : items) possible |= possible << i;
	for (int i = 0; i <= sm; i++)
		if (possible[i] && abs(2 * i - sm) <= k) return printf("YES\n"), 0;
	printf("NO\n");
	return 0;
}
