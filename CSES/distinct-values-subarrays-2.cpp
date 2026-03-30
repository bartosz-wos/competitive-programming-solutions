#include<iostream>
#include<map>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
int n, k, p, tab[200007];
long long ans;
map<int, int> mp;
int main() {
	ios;
	cin >> n >> k;
	for (int i = 0; i < n; ++i)
		cin >> tab[i];
 
	int poc = 0;
	for (int kon = 0; kon < n; ++kon) {
		while (poc < n && p + (mp[tab[poc]] == 0) <= k) {
			++mp[tab[poc]];
			p += (mp[tab[poc]] == 1);
			++poc;
		}
		ans += poc - kon;
		p -= (mp[tab[kon]] == 1);
		--mp[tab[kon]];
	}
	cout << ans;
}
