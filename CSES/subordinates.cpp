#include<iostream>
#include<vector>
#include<bitset>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
vector<int> g[200007];
int tab[200007];
 
int ans;
void dfs(int v, int e) {
	tab[v] = 1;
	for (const int& i : g[v]) {
		if (i == e) continue;
		dfs(i, v);
		tab[v] += tab[i];
	}
}
 
int n, m, a, b;
int main() {
	ios;
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		cin >> a;
		g[a].push_back(i);
		g[i].push_back(a);
	}
	dfs(1, -1);
	for (int i = 1; i <= n; ++i)
		cout << tab[i]-1 << ' ';
}
