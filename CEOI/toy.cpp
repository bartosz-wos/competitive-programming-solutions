#include <iostream>
#include <queue>

using namespace std;
const int N = 1505;
int a[N][N], up[N][N], down[N][N], lft[N][N], rgt[N][N], seen[N][N];

int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, m, k, l, xh, yh, xv, yv, tx, ty;
	cin>>m>>n>>k>>l>>xh>>yh>>xv>>yv;

	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++){
			char c;
			cin>>c;
			if (c == '*')
				tx = i, ty = j;
			a[i][j] = (c != 'X');
		}
	}

	for (int i=1;i<=n;i++){
		for (int j=1;j<=m;j++)
			lft[i][j] = (lft[i][j-1] + 1) * a[i][j];

		for (int j=m;j>=1;j--)
			rgt[i][j] = (rgt[i][j+1] + 1) * a[i][j];

		for (int j=1;j<=m;j++)
			up[i][j] = (up[i-1][j] + 1) * a[i][j];
	}

	for (int i=n;i>=1;i--)
		for (int j=1;j<=m;j++)
			down[i][j] = (down[i+1][j] + 1) * a[i][j];

	queue<pair<int,int>> Q;
	Q.push({yh +1, xv +1});
	seen[yh+1][xv+1] = 1;

	while (Q.size() > 0){
		auto [i, j] = Q.front();
		Q.pop();

		if (!seen[i+1][j] and min(lft[i][j], lft[i+1][j]) + min(rgt[i][j], rgt[i+1][j]) > k)
			seen[i+1][j] = 1, Q.push({i+1, j});

		if (!seen[i-1][j] and min(lft[i][j], lft[i-1][j]) + min(rgt[i][j], rgt[i-1][j]) > k)
			seen[i-1][j] = 1, Q.push({i-1, j});
		
		if (!seen[i][j+1] and min(up[i][j], up[i][j+1]) + min(down[i][j], down[i][j+1]) > l)
			seen[i][j+1] = 1, Q.push({i, j+1});
		
		if (!seen[i][j-1] and min(up[i][j], up[i][j-1]) + min(down[i][j], down[i][j-1]) > l)
			seen[i][j-1] = 1, Q.push({i, j-1});
	}
	cout<<(seen[tx][ty] ? "YES\n" : "NO\n");
}
