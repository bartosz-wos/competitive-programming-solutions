#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
 
int n, k;
string a;
int main() {
	cin >> n >> k;
	vector<int> tab(n, 0);
 
	for (int i = 0; i < n; ++i) {
		cin >> a;
		for (int j = k-1; j >= 0; --j)
			tab[i] += (a[j] == '1') * (1 << (k - j));
	}
	int ans = 32;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			ans = min(ans, __builtin_popcount(tab[i] ^ tab[j]));
	cout << ans;
}
