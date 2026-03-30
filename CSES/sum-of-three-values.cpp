#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
using pi = pair<int, int>;
#define ios ios::sync_with_stdio(false);
 
int n, x;
vector<pi> tab;
int main() {
	ios;
	cin >> n >> x;
	tab.resize(n);
	for (int i = 0; i < n; ++i)
		cin >> tab[i].first, tab[i].second = i + 1;
	sort(tab.begin(), tab.end());
	int lo, hi = n - 1, sum = 0;
 
	for (int i = 0; i < n; ++i) {
		lo = i + 1, hi = n - 1;
		while (lo < hi) {
			sum = tab[i].first + tab[lo].first + tab[hi].first;
			if (sum == x) {
				cout << tab[i].second << ' ' << tab[lo].second << ' ' << tab[hi].second;
				return 0;
			}
			else if (sum < x)
				++lo;
			else
				--hi;
		}
	}
	cout << "IMPOSSIBLE";
}
