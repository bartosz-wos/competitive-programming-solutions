#include<bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int mod = 1e9 + 7;
static ll tab[1000001];
int n;
 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	tab[1] = 0;
	cin >> n;
	for(int i = 2; i <= n; ++i)
		tab[i] = (tab[i-1] * i + (i & 1 ? -1 : 1)) % mod;
	
	cout << tab[n];
}
