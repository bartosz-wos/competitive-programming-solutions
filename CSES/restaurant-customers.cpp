#include<iostream>
#include<set>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
constexpr int MAXN = 2e5 + 7;
using pi = pair<int, int>;
 
multiset<pi> S;
int n, a, b;
int main() {
	ios;
	cin >> n;
	for(int i = 0; i < n; ++i) {
		cin >> a >> b;
		S.insert({a, 1});
		S.insert({b + 1, -1});
	}
 
	int ans = 0, many = 0;
	for(const pi& i : S) {
		many += i.second;
		ans = max(ans, many);
	}
	cout << ans;
}
