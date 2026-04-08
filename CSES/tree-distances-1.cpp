#include<iostream>
#include<bitset>
#include<queue>
#include<vector>
#include<array>
#include<algorithm>
using namespace std;
int n;
vector<int> g[200001];
array<int, 2> p1, p2;
int dist1[200001];
int dist2[200001];
 
void dfs(int v, int e, int d, array<int, 2>& p) {
	if (p[1] < d)
		p = { v, d };
	for (const int& i : g[v]) {
		if (i == e) continue;
		dfs(i, v, d + 1, p);
	}
}
 
void dist(int v, int e, int d[]) {
	for (const int& i : g[v]) {
		if (i == e) continue;
		d[i] = d[v] + 1;
		dist(i, v, d);
	}
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, -1, 0, p1);
	dfs(p1[0], -1, 0, p2);
	dist(p1[0], -1, dist1);
	dist(p2[0], -1, dist2);
 
	for (int i = 1; i <= n; ++i)
		cout << max(dist1[i], dist2[i]) << ' ';
}

