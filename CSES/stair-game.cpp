#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int t, n, p, ans;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> t;
	while(t--) {
		ans = 0;
		cin >> n;
		for(int i = 0; i < n; ++i) {
			cin >> p;
			if(i & 1) ans ^= p;
		}
		cout << (ans ? "first\n" : "second\n");
	}
}

