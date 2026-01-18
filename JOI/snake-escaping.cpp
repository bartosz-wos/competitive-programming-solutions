#pragma GCC optimize("O3")

#include <bits/stdc++.h>

int main() {
	using namespace std;
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);

	int L, Q;
	cin >> L >> Q;

	string S;
	cin >> S;
	vector<int> A(1 << L), dp1(1 << L), dp2(1 << L);
	for (int i = 0; i < (1 << L); i++)
		A[i] = dp1[i] = dp2[i] = S[i] - '0';
	
	for (int b = 0; b < L; b++) {
		for (int m = 0; m < (1 << L); m++) {
			if (m >> b & 1)
				dp1[m] += dp1[m ^ (1 << b)];
			else 
				dp2[m] += dp2[m ^ (1 << b)];
		}
	}
	
	while (Q--) {
		string S;
		cin >> S;
		reverse(S.begin(), S.end());
		int s0 = 0, s1 = 0, s2 = 0;
		int m0 = 0, m1 = 0, m2 = 0;
		for (int i = 0; i < L; i++) {
			char c = S[i];
			if (c == '?') {
				s2++;
				m2 |= (1 << i);
			} else if (c == '0') {
				s0++;
				m0 |= (1 << i);
			} else if (c == '1') {
				s1++;
				m1 |= (1 << i);
			}
		}

		int s = min({s0, s1, s2});
		if (s == s2) {
			int ans = A[m1];
			for (int m = m2; m > 0; m = (m - 1) & m2) 
				ans += A[m1 | m];
			cout << ans << '\n';
		} else if (s == s0) {
			int ans = dp2[m1];
			for (int m = m0; m > 0; m = (m - 1) & m0) {
				if (__builtin_popcount(m) % 2 == 0)
					ans += dp2[m1 | m];
				else 
					ans -= dp2[m1 | m];
			}
			cout << ans << '\n';
		} else if (s == s1) {
			int ans = s1 % 2 == 0 ? dp1[m2] : -dp1[m2];
			for (int m = m1; m > 0; m = (m - 1) & m1) {
				if (__builtin_popcount(m) % 2 == s1 % 2)
					ans += dp1[m2 | m];
				else 
					ans -= dp1[m2 | m];
			}
			cout << ans << '\n';
		}
	}
}
