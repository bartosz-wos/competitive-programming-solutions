#include<iostream>
#include<vector>
#include<bitset>
#include<stack>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
vector<int> g[100007];
vector<int> team(100007, -1);
bitset<100007> vis;
int n, m, a, b;
 
bool dfs(int v) {
	stack<int> S;
	team[v] = 1;
	vis[v] = 1;
	S.push(v);
	int u = 0;
	while (!S.empty()) {
		u = S.top();
		S.pop();
 
		for (const int& i : g[u]) {
			if (!vis[i]) {
				team[i] = ((team[u] == 1) ? 2 : 1);
				S.push(i);
				vis[i] = 1;
			}
			else if (team[i] == team[u])
				return 0;
		}
	}
	return 1;
}
 
 
int main() {
	ios;
	cin >> n >> m;
	while (m--) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
 
	bool ok = 0;
	for (int i = 1; i <= n; ++i)
		if (!vis[i]) {
			ok = dfs(i);
			if (!ok) {
				cout << "IMPOSSIBLE";
				return 0;
			}
		}
 
	for (int i = 1; i <= n; ++i)
		cout << team[i] << ' ';
}
