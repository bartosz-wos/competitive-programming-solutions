#include<bits/stdc++.h>
using namespace std;
using ar3 = array<int, 3>;
 
int grid[9][9];
int dx[] {-2, -2, -1, -1, 1, 1, 2, 2}, dy[] {-1, 1, -2, 2, -2, 2, -1, 1};
 
int deg(int x, int y) {
	int d = 0;
	for(int i = 0; i < 8; ++i) {
		int x2 = x + dx[i], y2 = y + dy[i];
		if(x2 >= 1 and x2 <= 8 and y2 >= 1 and y2 <= 8 and !grid[x2][y2])
			++d;
	}
	return d;
}
 
bool dfs(int mv, int x, int y) {
	grid[x][y] = mv;
	if(mv == 64)
		return true;
	vector<ar3> tab;
	for(int i = 0; i < 8; ++i) {
		int x2 = x + dx[i], y2 = y + dy[i];
		if(x2 >= 1 and x2 <= 8 and y2 >= 1 and y2 <= 8 and !grid[x2][y2]) {
			int d = deg(x2, y2);
			tab.push_back({d, x2, y2});
		}
	}
	sort(tab.begin(), tab.end());
	for(const auto& [d, x2, y2] : tab)
		if(dfs(mv + 1, x2, y2))
				return true;
	grid[x][y] = 0;
	return false;
}
 
void solve() {
	int x, y;
	cin >> y >> x;
	dfs(1, x, y);
	for(int i = 1; i <= 8; ++i) {
		for(int j = 1; j <= 8; ++j)
			cout << grid[i][j] << ' ';
		cout << '\n';
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
