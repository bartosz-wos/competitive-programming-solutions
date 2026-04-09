#include<bits/stdc++.h>
using namespace std;
 
int solve(int n, int k) {
	if(n == 1)
		return 1;
	if(k <= ((n + 1) >> 1)) {
		if(2 * k > n)
			return 2 * k % n;
		return 2 * k;
	}
	int p = solve(n >> 1, k - ((n + 1) >> 1));
	if(n & 1)
		return 2 * p + 1;
	return 2 * p - 1;
}
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int t;
	cin >> t;
	while(t--) {
		int n, k;
		cin >> n >> k;
		cout << solve(n, k) << '\n';
	}
}
