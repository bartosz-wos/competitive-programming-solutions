#include <iostream>
#include <map>
using namespace std;
 
bool vis[1007][1007];
int dx[] = { 0, 0, -1, 1 }, dy[] = { 1, -1, 0, 0 };
int n, m, ans;
 
string grid[1007];
 
void dfs_grid(int v, int w) {
	int i;
	vis[v][w] = true;
	for (i = 0; i < 4; i++) {
		pair <int, int> sasiad = make_pair(v + dx[i], w + dy[i]);
		if (1 <= sasiad.first && sasiad.first <= n && 1 <= sasiad.second && sasiad.second <= m) {
			if (!vis[sasiad.first][sasiad.second] && grid[sasiad.first][sasiad.second] == '.') {
				vis[sasiad.first][sasiad.second] = true;
				dfs_grid(sasiad.first, sasiad.second);
			}
		}
	}
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> grid[i];
		grid[i] = '0' + grid[i];
	}
 
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			if ( grid[i][j]  == '.' && !vis[i][j] ) {
				dfs_grid(i, j);
				++ans;
			}
	}
	cout << ans;
}
