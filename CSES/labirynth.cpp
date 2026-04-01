#include<iostream>
#include<bitset>
#include<queue>
using namespace std;
using pi = pair<int, int>;
int n, m, dist[1007][1007];
char grid[1007][1007];
bitset<1007> vis[1007];
int di[]{ 0, 0, 1, -1 }, dj[]{ 1, -1, 0, 0 };
pi parent[1007][1007];
#define pari parent[i][j].first
#define pars parent[i][j].second
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
bool check(const int& i, const int& j) {
	return ((i >= 1 && i <= n) && (j >= 1 && j <= m) && (grid[i][j] != '#') && ( !vis[i][j] ) );
}
 
void bfs(int i, int j) {
	queue<pi> Q;
	Q.push({ i, j });
	vis[i][j] = 1;
	
	pi sasiad;
	while (!Q.empty()) {
		i = Q.front().first;
		j = Q.front().second;
		Q.pop();
		for (int k = 0; k < 4; ++k) {
			sasiad = { i + di[k], j + dj[k] };
			if (check(sasiad.first, sasiad.second)) {
				Q.push(sasiad);
				vis[sasiad.first][sasiad.second] = 1;
				dist[sasiad.first][sasiad.second] = dist[i][j] + 1;
				parent[sasiad.first][sasiad.second] = { i, j };
			}
		}
	}
}
 
void print(int i, int j) {
	if (parent[i][j] == make_pair(0, 0))
		return;
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
 
pi A, B;
int main() {
	ios;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			cin >> grid[i][j];
			if (grid[i][j] == 'A')
				A.first = i, A.second = j;
			else if (grid[i][j] == 'B')
				B.first = i, B.second = j;
		}
	bfs(A.first, A.second);
	if (!dist[B.first][B.second]) {
		cout << "NO";
		return 0;
	}
	cout << "YES\n" << dist[B.first][B.second] << '\n';
	print(B.first, B.second);
}
