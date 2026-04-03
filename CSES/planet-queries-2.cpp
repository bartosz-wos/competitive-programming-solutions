#include<bits/stdc++.h>
using namespace std;
int n, q;
 
int ptr[200001][20];
int len[200001];
bitset<200001> vis;
 
void dfs(int v) {
	vis[v] = 1;
	if(!vis[ptr[v][0]])
		dfs(ptr[v][0]);
	len[v] = len[ptr[v][0]] + 1;
}
 
int jump(int v, int k) {
	if(k <= 0)
		return v;
	int j = 0;
	while(k) {
		if(k & 1)
			v = ptr[v][j];
		k >>= 1;
		++j;
	}
	return v;
}
 
void solve(){
	cin >> n >> q;
    	for(int i = 1; i <= n; ++i)
		cin >> ptr[i][0];
    	for (int i = 1; i < 20; ++i)
        	for (int j = 1; j <=n; ++j)
			ptr[j][i] = ptr[ptr[j][i-1]][i-1];
 
    	for(int i = 1; i <= n; ++i)
        	if (!vis[i])
            		dfs(i);
 
	while(q--) {
		int a, b;
		cin >> a >> b;
		int x = jump(a, len[a]);
		if(jump(a, len[a] - len[b]) == b)
			cout << len[a] - len[b] << '\n';
		else if(jump(x, len[x] - len[b]) == b)
			cout << len[a] + len[x] - len[b] << '\n';
		else
			cout << -1 << '\n';
	}
}    
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t = 1;
	while(t--)
		solve();
}
