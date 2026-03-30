#include<iostream>
#include<set>
#include<algorithm>
#include<array>
using namespace std;
#define ar array
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
auto comp = [](const ar<int, 2>& a, const ar<int, 2>& b) {return a[1] < b[1]; };
 
int n, k, ans;
ar<int, 2> tab[200007];
multiset<int> S;
int main() {
	ios;
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> tab[i][0] >> tab[i][1];
 
	sort(tab, tab + n, comp);
	for (int i = 0; i < n; ++i) {
		int x = -tab[i][0], y = -tab[i][1];
		if (!S.size()) {
			S.insert(y);
			++ans;
		}
		else {
			auto z = S.lower_bound(x);
			if (z == S.end()) {
				if (S.size() < k) {
					S.insert(y);
					++ans;
				}
			}
			else {
				S.erase(z);
				S.insert(y);
				++ans;
			}
		}
	}
	
	cout << ans;
}
