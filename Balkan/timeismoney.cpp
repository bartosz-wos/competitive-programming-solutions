#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
using pii = pair<int, int>;

// BeginCodeSnip{DSU}
struct DSU {
	vector<int> g;
	DSU(int n) : g(n, -1) {}
	int find(int a) { return g[a] < 0 ? a : (g[a] = find(g[a])); }
	/**
	 * If a and b are already in the same set, return false and do nothing.
	 * Otherwise, merge set a and b into one set and return true.
	 */
	bool unite(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		if (g[a] > g[b]) swap(a, b);
		g[a] += g[b];
		g[b] = a;
		return true;
	}
};
// EndCodeSnip

struct Edge {
	int x;
	int y;
	int time;
	int cost;
	int id;
};

/**
 * Kruskal's Algorithm to find a MST with given edges and weights. Returns the
 * time and cost as pair<int,int> as well as ids of edges of the MST as
 * vector<int>.
 */
pair<pii, vector<int>> kruskal(int n, vector<Edge> &edges,
                               vector<int> &weights) {
	sort(begin(edges), end(edges), [&](const Edge &e1, const Edge &e2) {
		return weights[e1.id] < weights[e2.id];
	});
	DSU dsu(n);
	vector<int> mst;
	int t = 0;
	int c = 0;
	for (Edge &e : edges) {
		if (dsu.unite(e.x, e.y)) {
			t += e.time;
			c += e.cost;
			mst.push_back(e.id);
		}
	}
	return {{t, c}, mst};
}

/**
 * Calculate the signed area of the triangle defined by the given points.
 * This value is negative if point P is on the right side of vector AB.
 */
ll area(pii A, pii B, pii P) {
	pii AB = {B.first - A.first, B.second - A.second};
	pii AP = {P.first - A.first, P.second - A.second};
	return AB.first * AP.second - AB.second * AP.first;
}

int main() {
	int N, M;
	cin >> N >> M;

	vector<Edge> edges(M);
	for (int i = 0; i < M; i++) {
		int x, y, t, c;
		cin >> x >> y >> t >> c;
		edges[i] = {x, y, t, c, i};
	}

	// The best Minimum Spanning Tree found so far.
	vector<int> best_MST;
	// The sum of time and cost w.r.t. best_MST.
	pii best_V = {1e8, 1e8};
	vector<int> current_MST;
	pii A, B, P;
	// The weights used by Kruskal's Algorithm to determine the MST.
	vector<int> weights(M);

	// A corresponds to the values of the MST if we only minimize the time
	for (int i = 0; i < M; i++) { weights[edges[i].id] = edges[i].time; }
	tie(A, best_MST) = kruskal(N, edges, weights);
	best_V = A;

	// B corresponds to values of the MST if we only minimize the cost
	for (int i = 0; i < M; i++) { weights[edges[i].id] = edges[i].cost; }
	tie(B, current_MST) = kruskal(N, edges, weights);
	// If solution B is better than A, update the best solution
	if ((ll)B.first * B.second < (ll)A.first * A.second) {
		best_V = B;
		best_MST = current_MST;
	}

	// Search recursively for points on lower convex hull of the solution space
	stack<pair<pii, pii>> to_search;
	to_search.push({A, B});
	while (!to_search.empty()) {
		auto [A, B] = to_search.top();
		to_search.pop();

		/*
		 * Since P is on the right side of vector AB, the signed area is
		 * negative. Thus, to maximize the unsigned area of triangle ABP, we
		 * should minimize this signed value.
		 */
		for (int i = 0; i < M; i++) {
			weights[edges[i].id] = (edges[i].cost * (B.first - A.first) -
			                        edges[i].time * (B.second - A.second));
		}
		tie(P, current_MST) = kruskal(N, edges, weights);

		/*
		 * If P is on the left side of vector AB, we can terminate the search
		 * on this branch. Note that the "left side of vector AB" is the right
		 * side on the coordinate system.
		 */
		if (area(A, B, P) >= 0) { continue; }

		// Compare the V value and update the best result if needed.
		if ((ll)P.first * P.second < (ll)best_V.first * best_V.second) {
			best_V = P;
			best_MST = current_MST;
		}

		/*
		 * Search further with the new acquired point P to see if there is
		 * another point that is on a hyperbola further left than P.
		 */
		to_search.push({A, P});
		to_search.push({P, B});
	}

	cout << best_V.first << " " << best_V.second << "\n";
	sort(begin(edges), end(edges),
	     [](const Edge &e1, const Edge &e2) { return e1.id < e2.id; });
	for (int &id : best_MST) {
		cout << edges[id].x << " " << edges[id].y << "\n";
	}
}
