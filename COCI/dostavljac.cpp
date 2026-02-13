#include <bits/stdc++.h>
using namespace std;

const int maxn = 510;

int n, m;
int A[maxn];

int dp[2][maxn][maxn];

vector<int> grafo[maxn];

void dfs(int u, int p)
{
	for (int i = 1; i <= m; i++)
		dp[0][u][i] = dp[1][u][i] = A[u];

	for (auto v: grafo[u])
	{
		if (v == p) continue;

		dfs(v, u);

		for (int i = m; i >= 1; i--)
		{
			for (int j = 0; j <= i; j++)
			{
				if (i >= j+1)
					dp[0][u][i] = max(dp[0][u][i], max(dp[0][v][j], dp[1][v][j]) + dp[1][u][i-j-1]);
				if (i >= j+2)
				{
					dp[0][u][i] = max(dp[0][u][i], dp[1][v][j] + dp[0][u][i-j-2]);
					dp[1][u][i] = max(dp[1][u][i], dp[1][v][j] + dp[1][u][i-j-2]);
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++)
		scanf("%d", &A[i]);

	for (int i = 1; i < n; i++)
	{
		int u, v;
		scanf("%d %d", &u, &v);

		grafo[u].push_back(v); grafo[v].push_back(u);
	}

	dfs(1, 0);

	printf("%d\n", max(dp[0][1][m], dp[1][1][m]));
}
