#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll P = 69421;
const ll M = 1e9 + 9;

int main() {
	int tc;
	cin >> tc;
	while (tc--) {
		string s;
		cin >> s;

		int n = s.length();
		int ans = 0;
		int found = 0;
		int start = 0;

		while (found != -1) {
			ll hash_left = 0, hash_right = 0;
			found = -1;
			for (ll l = start, pw = 1; l < n / 2; l++, pw = (pw * P % M)) {
				hash_left = (hash_left * P + s[l]) % M;
				hash_right = (hash_right + pw * s[n - 1 - l]) % M;
				if (hash_left == hash_right) {
					found = l;
					break;
				}
			}

			if (found != -1) {
				start = found + 1;
				ans += 2;
			}
		}

		if (start * 2 == n) {
			cout << ans << endl;
		} else {
			cout << ans + 1 << endl;
		}
	}
}
