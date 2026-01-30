#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int N = 18;
const int M = 998244353;
int a[N];
bool indepset[1 << N];
int popcnt[1 << N];
int ar[1 << N];
int nodeid[1 << N];
ll dp[1 << N];
int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		a[u] |= 1 << v;
		a[v] |= 1 << u;
	}
	for (int i = 0; i < n; i++) { nodeid[1 << i] = i; }
	for (int i = 0; i < (1 << n); i++) {
		popcnt[i] = popcnt[i >> 1] + (i & 1);
		ar[i] = (popcnt[i] % 2) * 2 - 1;
	}
	indepset[0] = 1;
	for (int i = 1; i < (1 << n); i++) {
		if (indepset[i & (i - 1)] && (a[nodeid[i & (-i)]] & (i & (i - 1))) == 0) {
			indepset[i] = true;
		}
	}
	dp[0] = 1;
	for (int i = 1; i < (1 << n); i++) {
		for (int j = i; j; j = (j - 1) & i) {
			if (indepset[j]) { dp[i] = (dp[i] + ar[j] * dp[i ^ j]) % M; }
		}
	}
	dp[(1 << n) - 1] = (dp[(1 << n) - 1] + M) % M;
	cout << dp[(1 << n) - 1] * m % M * ((M + 1) / 2) % M;
	return 0;
}
