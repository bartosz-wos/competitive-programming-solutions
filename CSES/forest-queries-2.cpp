#include<iostream>
using namespace std;
int tab[1001][1001];
int n, q;
 
void upd(int x, int y, int val) {
	for (; x <= n; x += x & -x)
		for (int j = y; j <= n; j += j & -j)
			tab[x][j] += val;
}
 
int query(int x, int y) {
	int ans = 0;
	for (; x; x -= x & -x)
		for (int j = y; j; j -= j & -j)
			ans += tab[x][j];
	return ans;
}
 
char grid[1001][1001];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			cin >> grid[i][j];
			if (grid[i][j] == '*')
				upd(i, j, 1);
		}
	while (q--) {
		int p;
		cin >> p;
		if (p == 1) {
			int y, x;
			cin >> y >> x;
			upd(y, x, grid[y][x] == '*' ? -1 : 1);
			grid[y][x] == '*' ? grid[y][x] = '.' : grid[y][x] = '*';
		}
		else {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			cout << query(c, d) - query(a - 1, d) - query(c, b - 1) + query(a-1, b-1) << '\n';
		}
	}
}
