#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#define INF 1e9
using namespace std;
typedef long long ll;

void solve()
{
	int n, k; cin >> n >> k;
	vector<ll>v(n), a;
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		a.push_back(v[i]);
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < n; i++) {
		int pos = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
		a[i] = pos/k;
	}
	vector<int>dp(n + 5, 1);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[j] <= a[i])dp[i] = max(dp[i], dp[j] + 1);
		}
	}
	int ans = 0;
	for (int i = 0; i < n; i++) ans = max(ans, dp[i]);
	cout << n - ans << "\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1; //cin>>t;
	while (t--) solve();
	return 0;
}
