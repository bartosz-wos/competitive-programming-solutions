#include <iostream>
#include <algorithm>
using namespace std;
long long tab[200007], w[200007], ans;
 
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> tab[i];
 
	ans = tab[n - 1];
	for (int i = n - 1; i >= 0; --i) {
		w[i] = max(w[i + 1] + tab[i], tab[i]);
		ans = max(ans, w[i]);
	}
	cout << ans;
}
