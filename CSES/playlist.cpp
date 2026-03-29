#include<iostream>
#include<map>
using namespace std;
 
int n, ans, tab[200007];
map<int, int> mp;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
 
	for(int i = 0, j = 0; i < n; ++i) {
		while(j < n && !mp[tab[j]]) {
			++mp[tab[j]];
			++j;
		}
		ans = max(ans, j - i);
		--mp[tab[i]];
	}
	cout << ans;
}
