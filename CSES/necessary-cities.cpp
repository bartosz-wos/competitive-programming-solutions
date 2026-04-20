#include<bits/stdc++.h>
using namespace std;
vector<int> g[100001];
int n, m, timer = 1;
set<int> ans;
int st[100001], low[100001];
 
void dfs(int v, int e) {
	st[v] = low[v] = timer++;
	int children = 0;
	for(const int& i : g[v]) {
		if(i == e) continue;
		if(st[i])
			low[v] = min(low[v], st[i]);
		else {
			dfs(i, v);
			low[v] = min(low[v], low[i]);
			if(e != -1 and low[i] >= st[v])
				ans.insert(v);
			++children;
		}
	}
	if(e == -1 and children > 1)
		ans.insert(v);
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	while(m--) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
 
	for(int i = 1; i <= n; ++i)
		if(!st[i])
			dfs(1, -1);
 
	cout << ans.size() << '\n';
	for(const int& i : ans)
		cout << i << ' ';
}
