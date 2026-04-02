#include<iostream>
#include<vector>
#include<bitset>
#include<queue>
using namespace std;
#define pb push_back
int n, m, a, b;
bitset<100007> vis;
vector<int> g[100007];
vector<int> dist(100007, 0);
int parent[100007];
 
void bfs(int v) {
	queue<int> Q;
	Q.push(v);
 
	while(!Q.empty()) {
		int u = Q.front();
		Q.pop();
 
		for(const int& i : g[u])
			if(!vis[i]) {
				vis[i] = 1; 
				Q.push(i);
				parent[i] = u; 
				dist[i] = dist[u] + 1;
				if(i==n) return;
			}
	}
}
 
void print(int n) {
	if(!n) return;
	print(parent[n]);
	cout << n << ' ';
}
 
int main() {
	cin >> n >> m;
 
	while(m--){
		cin >> a >> b;
		g[a].pb(b);
		g[b].pb(a);
	}
	bfs(1);
	parent[1] = 0;
	if(!dist[n]) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	cout << dist[n] + 1 << '\n';
	print(n);
 
}
