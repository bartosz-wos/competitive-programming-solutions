#include<iostream>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
long long n, k, tab[200007], sum;
 
bool check(long long m) {
	long long c = 1, s = 0;
	for (int i = 0; i < n; ++i) {
		if (tab[i] > m) return 0;
		if (s + tab[i] > m)
			++c, s = tab[i];
		else
			s += tab[i];
	}
	if (c <= k) return 1;
	return 0;
}
 
int main() {
	ios;
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> tab[i], sum += tab[i];
 
	long long lo = 0, hi = sum, ans = sum, mid;
	while (lo <= hi) {
		mid = (lo + hi) >> 1;
		if (check(mid)) {
			hi = mid - 1;
			ans = mid;
		}
		else
			lo = mid + 1;
	}
	cout << ans;
}
