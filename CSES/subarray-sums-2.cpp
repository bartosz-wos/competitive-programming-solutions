#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
using ll = long long;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
	int operator()(int x) const {return x ^ RANDOM;}
};
 
map<ll, int> mp;
 
int n, x, p;
ll sum, ans;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	mp[0] = 1;
	cin >> n >> x;
	while(n--) {
		cin >> p;
		sum += p;
		ans += mp[sum - x];
		++mp[sum];
	}
	cout << ans;
}
