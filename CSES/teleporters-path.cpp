#include<bits/stdc++.h>
using namespace std;
using ll = long long;
vector<int> g[100001];
int n, m;
static int ind[100001], out[100001];
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	for(int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		++out[a];
		++ind[b];
	}
 
	if(out[1] != ind[1] + 1 or ind[n] != out[n] + 1) {
		cout << "IMPOSSIBLE";
		exit(0);
	}
 
	for(int i = 2; i < n; ++i)
		if(ind[i] ^ out[i]) {
			cout << "IMPOSSIBLE";
			exit(0);
		}
 
	vector<int> res;
	stack<int> S;
	S.push(1);
	while(!S.empty()) {
		int u = S.top();
		if(g[u].empty()) {
			res.push_back(u);
			S.pop();
		}
		else {
			int v = g[u].back();
			g[u].pop_back();
			S.push(v);
		}
	}
 
	if(res.size() != m + 1) {
		cout << "IMPOSSIBLE";
		exit(0);
	}
 
	for(vector<int>::reverse_iterator it = res.rbegin(); it != res.rend(); ++it)
		cout << *it << ' ';
}
