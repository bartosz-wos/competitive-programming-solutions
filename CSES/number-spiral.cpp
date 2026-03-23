#include <iostream>
using namespace std;
#define int long long
 
int t, ans, x, y, z, z2;
signed main() {
	cin >> t;
 
	while (t--) {
		cin >> y >> x;
		z = max(y, x);
		z2 = (z - 1) * (z - 1);
		if (z & 1) {
			if (y == z)
				ans = z2 + x;
			else
				ans = z2 + 2 * z - y;
		}
		else {
			if (x == z)
				ans = z2 + y;
			else
				ans = z2 + 2 * z - x;
		}
		cout << ans << '\n';
	}

