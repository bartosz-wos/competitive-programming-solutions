#include<iostream>
#include<bitset>
using namespace std;
#define ios ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
 
bitset<100007> vis, pom;
int n, p, ans;
int main() {
	vis[0] = 1;
	cin >> n;
	while (n--) {
		cin >> p;
		for (int i = 0; i <= 100000 - p; ++i)
			if (vis[i] && !vis[i + p])
				pom[i + p] = 1, ++ans;
		vis |= pom;
	}
 
	cout << ans << '\n';
	for (int i = 1; i <= 100000; ++i)
		if (vis[i])
			cout << i << ' ';
}
