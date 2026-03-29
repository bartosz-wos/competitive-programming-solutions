#include<iostream>
#include<algorithm>
#include<array>
#include<set>
using namespace std;
using pi = pair<int, int>;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
#define ar array
 
int n, ans[200007];
ar<int, 3> a[200007];
int main() {
	ios;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i][1] >> a[i][0];
		a[i][2] = i;
	}
	sort(a, a + n); 
	set<ar<int, 2>> S;
	for (int i = 0; i < n; ++i) {
		auto it = S.lower_bound({a[i][1]});
		if (it != S.begin()) {
			--it;
			ans[a[i][2]] = (*it)[1];
			S.erase(it);
		}
		else
			ans[a[i][2]] = S.size();
		S.insert({ a[i][0], ans[a[i][2]] });
	}
 
	cout << S.size() << '\n';
	for (int i = 0; i < n; ++i)
		cout << ans[i] + 1 << ' ';
}
