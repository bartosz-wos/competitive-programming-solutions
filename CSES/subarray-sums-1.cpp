#include <iostream>
using namespace std;
 
int tab[200007], n, x, ans;
unsigned long long sum;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> x;
 
	for (int i = 0; i < n; ++i)
		cin >> tab[i];
 
	int poc = 0;
	for (int kon = 0; kon < n; ++kon) {
		while (poc < n && sum + tab[poc] <= x) {
			sum += tab[poc];
			if (sum == x)
				++ans;
			++poc;
		}
		sum -= tab[kon];
	}
	cout << ans;
}
