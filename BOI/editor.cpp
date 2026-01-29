#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 3e5 + 1;
const int MAX_D = 19;

int state[MAX_N], par[MAX_N][MAX_D], lev[MAX_N];

int get_par(int x, int max_lev) {
	if (lev[x] <= max_lev) { return x; }
	for (int i = MAX_D - 1; i >= 0; i--) {
		if (lev[par[x][i]] > max_lev) { x = par[x][i]; }
	}
	return par[x][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
	int n;
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> state[i];
		if (state[i] < 0) {
			lev[i] = -state[i];
			int z = get_par(i - 1, lev[i] - 1);
			par[i][0] = get_par(z - 1, lev[i] - 1);
			for (int j = 1; j < MAX_D; j++) {
				par[i][j] = par[par[i][j - 1]][j - 1];
			}
		}
		std::cout << state[get_par(i, 0)] << '\n';
	}
}
