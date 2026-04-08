#include<bits/stdc++.h>
using namespace std;
int n, q, anc[200001][20];
 
int query(int v, int k) {
	int j = 0;
	while(k) {
		if(k & 1)
			v = anc[v][j];
		k >>= 1;
		++j;
	}
	return v;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q;
	for(int i = 2; i <= n; ++i) {
		int p;
		cin >> p;
		anc[i][0] = p;
	}
 
	for(int i = 1; i < 20; ++i)
		for(int j = 1; j <= n; ++j)
			anc[j][i] = anc[anc[j][i-1]][i-1];
 
	while(q--) {
		int v, w;
		cin >> v >> w;
		int ans = query(v, w);
		cout << (!ans ? -1 : ans) << '\n';
	}
}
