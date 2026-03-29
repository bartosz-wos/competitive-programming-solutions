#include<bits/stdc++.h>
using namespace std;
int n, t, tab[200001];
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> t;
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
	long long l = 0, r = 1e18, mid = 0, sum = 0, ans = 0;
	while(l <= r) {
		mid = (l + r) >> 1;
		sum = 0;
		for(int i = 0; i < n; ++i) {
			sum += mid / tab[i];
			if(sum >= t)
				break;
		}
 
		if(sum >= t) {
			ans = mid;
			r = mid - 1;
		}
		else
			l = mid + 1;
	}
	cout << ans;
}
