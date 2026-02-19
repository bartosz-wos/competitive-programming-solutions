#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int cmp[100001];
ll sz[100001], ans = 0;
set<int> child[100001], graph[100001], rgraph[100001];
queue<pair<int, int>> to_merge;

void insert_weak_connection(int A, int B) {
	graph[A].insert(B);
	rgraph[B].insert(A);
	// If there's A new strong connection between A's and B's components, merge
	// them
	if (graph[B].count(A)) to_merge.push({A, B});
}

int dsu_size(int A) { return child[A].size() + graph[A].size() + rgraph[A].size(); }

int find(int A) { return (A == cmp[A] ? A : cmp[A] = find(cmp[A])); }

void onion(int A, int B) {
	if (A == B) return;
	// Merge the smaller component into the larger
	if (dsu_size(A) < dsu_size(B)) swap(A, B);

	// Add new contribution
	ans += sz[B] * child[A].size() + sz[A] * child[B].size();

	// DSU stuff
	cmp[B] = A;
	sz[A] += sz[B];

	// Merge children of B into A
	for (int i : child[B]) {
		if (child[A].count(i)) ans -= sz[A];
		else child[A].insert(i);
	}
	// Erase the connections
	graph[A].erase(B), rgraph[A].erase(B);
	graph[B].erase(A), rgraph[B].erase(A);
	// Merge the weak connections to other components
	for (int i : graph[B]) {
		rgraph[i].erase(B);
		insert_weak_connection(A, i);
	}
	for (int i : rgraph[B]) {
		graph[i].erase(B);
		insert_weak_connection(i, A);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cmp[i] = i;
		sz[i] = 1;
		child[i].insert(i);
	}
	while (m--) {
		int A, B;
		cin >> A >> B;

		B = find(B);
		// If A isn't in B's component and doesn't already follow someone in B's
		// component...
		if (find(A) != B && !child[B].count(A)) {
			// We insert A as A follower of B and add sz[find(B)] to the answer
			child[B].insert(A);
			ans += sz[B];

			A = find(A);
			// Add connections between components
			insert_weak_connection(A, B);
			// We may have to merge multiple components for each new event
			while (to_merge.size()) {
				tie(A, B) = to_merge.front();
				to_merge.pop();
				onion(find(A), find(B));
			}
		}
		cout << ans << '\n';
	}
	return 0;
}
