#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
int n, m, a, b;
vector<int> order;
vector<int> g[100007];
 
bool toposort() {
	vector<int> ind(n + 1, 0);
	queue<int> Q;
	for (int i = 1; i <= n; ++i)
		for (const int& j : g[i])
			++ind[j];
	for (int i = 1; i <= n; ++i)
		if (!ind[i])
			Q.push(i);
	int u = 0;
	while (!Q.empty()) {
		u = Q.front();
		Q.pop();
		order.push_back(u);
		for (const int& i : g[u])
			if (--ind[i] == 0)
				Q.push(i);
	}
	return order.size() == n;
}
 
int main() {
	ios;
	cin >> n >> m;
	while (m--) {
		cin >> a >> b;
		g[a].push_back(b);
	}
	if (toposort())
		for (const int& i : order)
			cout << i << ' ';
	else
		cout << "IMPOSSIBLE";
}
