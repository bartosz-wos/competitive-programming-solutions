#include<iostream>
#include<vector>
#include<set>
#include<climits>
using namespace std;
using ll = long long;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
int n, a, b, p;
ll pfx[200007], ans = LLONG_MIN;
multiset<ll> S;
int main() {
	ios;
	cin >> n >> a >> b;
	for (int i = 1; i <= n; ++i)
		cin >> p, pfx[i] = pfx[i - 1] + p;
 
	for (int i = a; i <= n; ++i) {
		if (i > b) S.erase(S.find(pfx[i - b - 1]));
		S.insert(pfx[i - a]);
		ans = max(ans, pfx[i] - *S.begin());
	}
	cout << ans;
}
