#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using pi = pair<int, int>;
 
int n, a, b;
long long ans, t;
int main() {
	cin >> n;
	vector<pi> tab(n);
	for (int i = 0; i < n; ++i) {
		cin >> a >> b;
		tab[i].first = a, tab[i].second = b;
	}
	sort(tab.begin(), tab.end());
 
	for (int i = 0; i < n; ++i) {
		t += tab[i].first;
		ans += tab[i].second - t;
	}
	cout << ans;
}
