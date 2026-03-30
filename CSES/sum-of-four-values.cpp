#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
 
long long tab[1007], n, x, sum;
map<int, vector<pi>> mp;
int main() {
	ios;
	cin >> n >> x;
	for (int i = 1; i <= n; ++i) {
		cin >> tab[i];
		for (int j = 1; j < i; ++j) {
			sum = tab[i] + tab[j];
			if (sum >= x) continue;
			if (mp.find(x - sum) != mp.end()) {
				for (const pi& k : mp[x - sum]) {
					if (k.first != j && k.second != j && k.first != i && k.second != i) {
						cout << k.first << ' ' << k.second << ' ' << j << ' ' << i;
						return 0;
					}
				}
			}
			mp[sum].push_back({ j, i });
		}
	}
	cout << "IMPOSSIBLE";
}
