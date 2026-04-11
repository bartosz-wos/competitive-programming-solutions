#include<iostream>
#include<vector>
using namespace std;
constexpr int mod = 1e9 + 7;
using ll = long long;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
using vvl = vector<vector<ll>>;
int n, m, k, a, b;
vvl mul(vvl a, vvl b) {
	vvl P(n, vector<ll>(n, 0));
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			for (int k = 0; k < n; ++k)
				P[i][j] = (P[i][j] + a[i][k] * b[k][j] % mod) % mod;
	return P;
}
 
ll exp(vvl& a, int w) {
	vvl P(n, vector<ll>(n, 0));
	for (int i = 0; i < n; ++i) P[i][i] = 1;
	while (w) {
		if (w & 1)
			P = mul(P, a);
		a = mul(a, a);
		w >>= 1;
	}
	return P[0][n - 1];
}
 
vvl g;
int main() {
	ios;
	cin >> n >> m >> k;
	g.resize(n, vector<ll>(n, 0));
	while (m--) {
		cin >> a >> b;
		++g[a - 1][b - 1];
	}
	cout << exp(g, k);
}
