#include<iostream>
#include<algorithm>
using namespace std;
constexpr int MAXN = 2e5 + 7;
 
int n, tab[MAXN];
long long ans = 1;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
	sort(tab, tab + n);
 
	for(int i = 0; i < n; ++i) {
		if(tab[i] <= ans)
			ans += tab[i];
	}
	cout << ans;
}
