#include <bits/stdc++.h>
using namespace std;

#define fast ios::sync_with_stdio(0);cin.tie(0);
#define s second
#define f first
typedef long long ll;
const ll MOD = 998244353;
const ll LOGN = 20; 
const ll MAXN = 5e6 + 101;

struct Edge {
	int to;
	short cost;
	char cap;
	Edge(int _to, short _cost, char _cap) : to(_to), cost(_cost), cap(_cap) { }
}; 

struct Flow {
	vector<Edge> edges;
	vector<int> from, nxt, boss;
	vector<short> dist;
	int n_, Q, source, terminal;
	Flow(int n) {
		Q = -1;
		n_ = n;
		dist = vector<short>(n);
		boss = vector<int>(n, -1);
		from = vector<int>(n);
	}
	void addEdge(int from, int to, int cost, int cap) {
		Q++;
		edges.push_back(Edge(to, cost, cap));
		nxt.push_back(boss[from]);
		boss[from] = Q;
		Q++;
		edges.push_back(Edge(from, -cost, 0));
		nxt.push_back(boss[to]); 
		boss[to] = Q;
	}
	bool SPFA() {
		queue<int> q;
		vector<bool> que(n_, 0); 
		for (int i = 0; i < dist.size(); i++)
			dist[i] = 10000;

		dist[source] = 0;
		que[source] = 1;
		q.push(source);
		while (!q.empty()) {
			int node = q.front();
			q.pop();
			que[node] = false;

			for (int u = boss[node]; u >= 0; u = nxt[u]) {
				if (edges[u].cap && dist[edges[u].to] > edges[u].cost + dist[node]) {
					dist[edges[u].to] = edges[u].cost + dist[node];
					from[edges[u].to] = u;
					if (!que[edges[u].to]) {
						q.push(edges[u].to);
						que[edges[u].to] = true;
					}
				}
			}
		}
		return (dist[terminal] != 10000);
	}
	ll minCost() {
		ll cost = 0;
		while (SPFA()) {
			cost += dist[terminal];
			int now = terminal;

			while (now != source) {
				int edge_id = from[now];
				int from = edges[edge_id ^ 1].to;
				now = from;
				edges[edge_id].cap--;
				edges[edge_id ^ 1].cap++;
			}
		}
		return cost;
	}
};

short grid[2005][2005];
int main() {
	fast
	int N, K;
	cin >> N >> K;

	ll ans = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> grid[i][j];
			ans += grid[i][j];
		}
	}

	Flow F = Flow(N * N + 10);
	F.addEdge(N * N + 2, 0, 0, K);
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= N; j++) {
			if ((i + 1 + j) % 2)
				F.addEdge(0, i * N + j, -grid[i][j], 1);
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= N; j++) {
			if ((i + 1 + j) % 2) {
				if (j != N)
					F.addEdge(i * N + j, i * N + j + 1, 0, 1);
				if (i != N - 1)
					F.addEdge(i * N + j, (i+1) * N + j, 0, 1);
				if (j != 1)
					F.addEdge(i * N + j, i * N + j - 1, 0, 1);
				if (i != 0)
					F.addEdge(i * N + j, (i-1) * N + j, 0, 1);
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 1; j <= N; j++) {
			if ((i + 1 + j) % 2 == 0)
				F.addEdge(i * N + j, N * N + 1, -grid[i][j], 1);
		}
	}
	F.source = N * N + 2, F.terminal = N * N + 1;

	ans += F.minCost();
	cout << ans << "\n";
}
