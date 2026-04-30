#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, x;
int h[101], s[101];
vector<int> pages, price;
ll dp[100001];
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n >> x;
	for(int i = 0; i < n; ++i)
		cin >> h[i];
	for(int i = 0; i < n; ++i)
		cin >> s[i];
	for(int i = 0; i < n; ++i) {
		int k, x = 1;
		cin >> k;
		while(k - x >= 0) {
			price.push_back(x * h[i]);
			pages.push_back(x * s[i]);
			k -= x;
			x <<= 1;
		}
		if(k) {
			price.push_back(k * h[i]);
			pages.push_back(k * s[i]);
		}
	}
	n = price.size();
	for(int i = 0; i < n; ++i)
		for(int j = x; j; --j)
			if(j - price[i] >= 0)
				dp[j] = max(dp[j], dp[j - price[i]] + pages[i]);
	cout << dp[x];
}
