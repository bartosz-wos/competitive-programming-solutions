#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
int add (int a, int b) {
	a += b; if (a >= MOD) a -= MOD;
	return a;
}
int sub (int a, int b) {
	a -= b; if (a < 0) a += MOD;
	return a;
}
int mul (int a, int b) {
	return (a * 1ll * b) % MOD;
}
int nCr[2001][2001];
int pre[2001][26][26];
string s; int n, q;
vector <int> occ[26];
int main () {
	for (int i = 0; i <= 2000; i++) {
		for (int j = 0; j <= i; j++) {
			if (j == i || j == 0) nCr[i][j] = 1;
			else nCr[i][j] = add(nCr[i - 1][j], nCr[i - 1][j - 1]);
		}
	}
	ios::sync_with_stdio(0); cin.tie(0);
	cin.tie(0);
	cin >> s; n = s.length();
	for (int i = n - 1; i >= 0; i--) occ[s[i] - 'a'].push_back(i);
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			for (int l = 2; l <= n; l++) {
				int p = 0;
				for (int q = 0; q < (int)occ[j].size(); q++) {
					while (p < (int)occ[i].size() && occ[i][p] > occ[j][q]) p++;
					pre[l][j][i] = add(pre[l][j][i], mul(p, nCr[occ[j][q]][l - 2]));
				}
			}	
		}
	}
	cin >> q;
	while (q--) {
		int t; cin >> t; char a, b; cin >> a >> b;
		cout << pre[t][a - 'a'][b - 'a'] << '\n';
	}
}
