#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;
 
vector<int> tab;
int n;
long long ans;
int main() {
	cin >> n;
	tab.resize(n);
	for(int i = 0; i < n; ++i)
		cin >> tab[i];
	sort(tab.begin(), tab.end());
	int med = tab[n >> 1];
	for(int i = 0; i < n; ++i)
		ans += abs( tab[i] - med );
 
	cout << ans;
}
