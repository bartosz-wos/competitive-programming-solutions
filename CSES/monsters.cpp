#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define pari parent[i][j].first
#define pars parent[i][j].second
int n, m;
char grid[1007][1007];
int dist[1007][1007];
pi parent[1007][1007];
bitset<1007> vis[1007];
queue< pair<pi, bool> > Q;
 
bool check(const int& i, const int& j) {
	return ( (i >= 1 && i <= n) && (j >= 1 && j <= m) && ( grid[i][j] != '#') && (!vis[i][j]));
}
 
int di[]{ 0, 0, 1, -1 }, dj[]{ 1, -1, 0, 0 };
 
pi bfs() {
	pair<pi, bool> sas;
	int i = 0, j = 0;
	bool typ = 0;
	while (!Q.empty()) {
		i = Q.front().first.first;
		j = Q.front().first.second;
		typ = Q.front().second;
		Q.pop();
		for(int k = 0; k < 4; ++k) {
			sas = {{i + di[k], j + dj[k]}, typ};
			if(check(sas.first.first, sas.first.second)) {
				vis[sas.first.first][sas.first.second] = 1;
				Q.push({{sas.first.first, sas.first.second}, typ});
				if(typ) {
					dist[sas.first.first][sas.first.second] = dist[i][j] + 1;
					parent[sas.first.first][sas.first.second] = {i, j};
					if(sas.first.first == 1 or sas.first.first == n or sas.first.second == 1 or sas.first.second == m)
						return {sas.first.first, sas.first.second};
				}
			}
		}
	}
	return make_pair(0, 0);
}
 
void print(const int i, const int j) {
	if (parent[i][j] == make_pair(0, 0)) return;
	print(pari, pars);
	if (i == pari + 1)
		cout << 'D';
	else if (i == pari - 1)
		cout << 'U';
	else if (j == pars + 1)
		cout << 'R';
	else if (j == pars - 1)
		cout << 'L';
}
 
pi A, ans;
int main() {
	ios;
	cin >> n >> m;
 
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			cin >> grid[i][j];
			if (grid[i][j] == 'A') {
				A.first = i, A.second = j;
				vis[i][j] = 1;
				if (i == 1 or j == 1 or i == n or j == m) {
					cout << "YES\n" << 0;
					return 0;
				}
			}
			else if (grid[i][j] == 'M') {
				Q.push({ {i, j},0 });
				vis[i][j] = 1;
			}
		}
	Q.push({{A.first, A.second}, 1});
	ans = bfs();
	if (ans == make_pair(0, 0)) {
		cout << "NO";
		return 0;
	}
	cout << "YES\n";
	cout << dist[ans.first][ans.second] << '\n';
	print(ans.first, ans.second);
}
