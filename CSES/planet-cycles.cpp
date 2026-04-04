#include<bits/stdc++.h>
using namespace std;
bitset<200001> vis;
int dest[200001];
int len[200001];
int n, steps;
queue<int> path;
 
void dfs(int v) {
	path.push(v);
	if(vis[v]) {
		steps += len[v];
		return;
	}
	vis[v] = 1;
	++steps;
	dfs(dest[v]);
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; ++i)
		cin >> dest[i];
 
	for(int i = 1; i <= n; ++i)
		if(!vis[i]) {
			steps = 0;
			dfs(i);
			int dec = 1;
			while(!path.empty()) {
				if(path.front() == path.back())
					dec = 0;
				len[path.front()] = steps;
				steps -= dec;
				path.pop();
			}
		}
 
	for(int i = 1; i <= n; ++i)
		cout << len[i] << ' ';
}
