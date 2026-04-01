#include<bits/stdc++.h>
using namespace std;
using ar = array<int, 3>;
using ll = long long;
constexpr int poz = 20;
constexpr int u = 1 << (poz - 1);
int n;
static ll dp[u << 1];
static ar tab[200001];
 
map<int, int> mp;
 
void act(int index, ll val) {
	index += u - 1;
	dp[index] = val;
	index >>= 1;
	while(index)
		dp[index] = max(dp[index << 1], dp[(index << 1) + 1]), index >>= 1;
}
 
ll query(int a, int b) {
	a += u - 2;
	b += u;
	ll ans = 0;
	while(b - a > 1) {
		if(!(a & 1))
			ans = max(ans, dp[a + 1]);
		if(b & 1)
			ans = max(ans, dp[b - 1]);
		a >>= 1;
		b >>= 1;
	}
	return ans;
}
 
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for(int i = 1; i <= n; ++i)
		cin >> tab[i][0] >> tab[i][1] >> tab[i][2];
	sort(tab + 1, tab + n + 1, [](const ar& a, const ar& b) {return a[1] < b[1];});
 
	for(int i = 1; i <= n; ++i) {
		dp[i + u - 1] = tab[i][2];
		mp[-tab[i][1]] = i;
	}
	for(int i = u - 1; i; --i)
		dp[i] = max(dp[i<<1], dp[(i<<1)+1]);
 
	map<int, int>::const_iterator it;
	for(int i = 1; i <= n; ++i) {
		it = mp.upper_bound(-tab[i][0]);
		if(it == mp.end())
			continue;
		int j = it->second;
		act(i, dp[i + u - 1] + query(1, j));
	}
	cout << query(1, n);
}
