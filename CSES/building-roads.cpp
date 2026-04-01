#include<iostream>
#include<vector>
#include<bitset>
#include<stack>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
struct par{
	int a = 0;
	int b = 0;
};
 
bitset<100007> vis;
vector<int> g[100007];
vector<int> odp;
 
void dfs(int v) {
	stack<int> S;
	S.push(v);
	vis[v] = true;
	int u = 0;
	while(!S.empty()) {
		u = S.top();
		S.pop();
 
		for(const int& k : g[u])
			if(!vis[k])
				S.push(k), vis[k] = true;
	}
}
 
int n, m, a, b, ans;
int main() {
	ios;
	cin >> n >> m;
	while(m--) {
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
 
	for(int i = 1; i <= n; ++i)
		if(!vis[i])
			dfs(i), ++ans, odp.push_back(i);
 
	cout << ans - 1 << '\n';
	if(ans == 1)
	return 0;
	for(int i = 1; i < odp.size(); ++i)
		cout << odp[i-1] << ' ' << odp[i] << '\n';
}
