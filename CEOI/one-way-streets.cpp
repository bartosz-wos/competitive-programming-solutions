#include<bits/stdc++.h>
     
using namespace std;
int n, m, p, u, v, lead[100005], low[100005], num[100005], d = 0, cnt = 0, ans[100005], timer = 0, q, val[100005];
vector<pair<int,int>> adj[100005];
vector<pair<int,int>> adj2[100005], edge;
stack<int> s;
bool mark[100005];
void dfs(int u, int id) {
	low[u] = num[u] = ++d;
	s.push(u);
	for (pair<int, int> W: adj[u]) {
		int node = W.first;
		if(W.second == id) continue;
		if(num[node] != 0) low[u] = min(low[u], num[node]);
		else {
			dfs(node, W.second);
			low[u] = min(low[u], low[node]);
		}
	}
	if(low[u] == num[u]) {
		cnt++;
		while(s.top() != u) lead[s.top()] = cnt, s.pop();
		lead[s.top()] = cnt, s.pop();
	}
}
void cal(int u, int par) {
	for (pair<int, int> node: adj2[u]) {
		if(mark[node.first]) continue;
		mark[node.first] = true;
		cal(node.first, u);
		val[u] += val[node.first];
	}
}
void get_ans(int u, int par) {
	for (pair<int, int> node: adj2[u]) {
		if(mark[node.first]) continue;
		mark[node.first] = true;
		int x, y;
		x = u, y = node.first;
		int id = node.second;
		//cout << "QWFQWF " << x << ' ' << y  << ' ' << id << '\n';
		if(val[node.first] < 0) {
			//cout << "EDGE " << x << ' ' << y << ' ' << edge[id].first << ' ' << edge[id].second << '\n';
			if(lead[edge[id].first] == x && lead[edge[id].second] == y) ans[id+1] = 1;
			else ans[id+1] = 2;
		}
		else if(val[node.first] > 0) {
			//cout << "EDGE " << x << ' ' << y << ' ' << edge[id].first << ' ' << edge[id].second << '\n';
			if(lead[edge[id].first] == x && lead[edge[id].second] == y) ans[id+1] = 2;
			else ans[id+1] = 1;
		}
		else ans[id+1] = 0;
		get_ans(node.first, u);
	}
}
void solve() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> u >> v;
		edge.push_back({u,v});
		adj[u].push_back({v,i});
		adj[v].push_back({u,i});
	}
	for (int i = 1; i <= n; i++) {
		if(num[i] == 0) dfs(i, -1);
	}
	int idx = 0;
	for (pair<int, int> i: edge) {
		if(lead[i.first] != lead[i.second]) adj2[lead[i.first]].push_back({lead[i.second], idx}), adj2[lead[i.second]].push_back({lead[i.first],idx});
		idx++;
	}
	cin >> q;
	while(q--) {
		cin >> u >> v;
		u = lead[u];
		v = lead[v];
		val[u]++;
		val[v]--;
	}
	for (int i = 1; i <= cnt; i++) if(!mark[i]) cal(i,-1);
	memset(mark, 0, sizeof(mark));
	for (int i = 1; i <= cnt; i++) if(!mark[i]) get_ans(i, -1);
	for (int i = 1; i <= m; i++) if(ans[i] == 0) cout << 'B'; else if(ans[i] == 1) cout << 'R'; else cout << 'L';
}
 
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	if(fopen("input.inp","r")){
		freopen("input.inp", "r", stdin);
		freopen("output.out", "w", stdout);
	}
	int t = 1;
	// cin >> t;
	while(t--) {
		solve();
	}
}
