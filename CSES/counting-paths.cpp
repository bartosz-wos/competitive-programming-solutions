#include<bits/stdc++.h>
using namespace std;
vector<int> g[200001];
int ptr[200001][20];
int depth[200001];
int val[200001];
int n, m;
 
void dfs(int v, int e) {
	for(int i = 1; i < 20; ++i)
		ptr[v][i] = ptr[ptr[v][i-1]][i-1];
	for(const int& i : g[v]) {
		if(i == e) continue;
		depth[i] = depth[ptr[i][0] = v] + 1;
		dfs(i, v);
	}
}
 
int jump(int v, int k) {
	int j = 0;
	while(k) {
		if(k & 1)
			v = ptr[v][j];
		k >>= 1;
		++j;
	}
	return v;
}
 
int lca(int a, int b) {
	if(depth[a] < depth[b])
		swap(a, b);
	a = jump(a, depth[a] - depth[b]);
	if(a == b)
		return a;
	for(int i = 19; i >= 0; --i) {
		int at = ptr[a][i], bt = ptr[b][i];
		if(at != bt)
			a = at, b = bt;
	}
	return ptr[a][0];
}
 
void dfs2(int v, int e) {
	int x = val[v];
	for(const int& i : g[v]) {
		if(i == e) continue;
		dfs2(i, v);
		x += val[i];
	}
	val[v] = x;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	for(int i = 2; i <= n; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	dfs(1, -1);
	while(m--) {
		int a, b;
		cin >> a >> b;
		++val[a];
		++val[b];
		int x = lca(a, b);
		--val[x];
		if(ptr[x][0])
			--val[ptr[x][0]];
	}
	dfs2(1, -1);
	for(int i = 1; i <= n; ++i)
		cout<< val[i] << ' ';
 
}
